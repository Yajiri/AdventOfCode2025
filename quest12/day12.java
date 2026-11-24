package quest12;
import java.io.*;
import java.util.*;
import java.time.*;

//should be Day12 but keeping it consistent with previous naming v´conventions.
class day12 {
    public static class Net extends ArrayList<List<Character>> {}
    public static class Board extends ArrayList<List<Integer>> {}
    public static class Puzzle {
        //final makes it immutable after creation. 
        public final int width;
        public final int height;
        public final int[] requirements;
    
        public Puzzle(int width, int height, int[] requirements) {
            this.width = width;
            this.height = height;
            this.requirements = requirements;
        }
    }
    static class ParsedInput {
    final List<Net> nets;
    final List<Puzzle> puzzles;

    ParsedInput(List<Net> nets, List<Puzzle> puzzles) {
        this.nets = nets;
        this.puzzles = puzzles;
    }
}

static boolean allCountsZero(int[] counts) { 
    for (int c : counts) {
        if(c != 0) {
            return false;
        }
    }
    return true; 
}

static Net rotate90(Net net) { 
    int h = net.size();
    int w = net.get(0).size();
    Net rotated = new Net();

    for (int x = 0; x < w; x++) {
        List<Character> row = new ArrayList<>();
        for (int y = 0; y < h; y++) {
            row.add('.');
        }
        rotated.add(row);
    }
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            rotated.get(x).set(h - 1- y, net.get(y).get(x));
        }
    }
    return rotated; 
}

static Net cloneNet(Net net) {
    Net copy = new Net();

    for (List<Character> row : net) {
        copy.add(new ArrayList<>(row));
    }
    return copy;
}

static List<Net> generateRotations(Net net) {
        List<Net> forms = new ArrayList<>();

        Net current = cloneNet(net);

        for (int i = 0; i < 4; i++) {
            boolean alreadySeen = false;

            for (Net form : forms) {
                if (form.equals(current)) {
                    alreadySeen = true;
                    break;
                }
            }
            if (!alreadySeen) {
                forms.add(cloneNet(current));
            }
            current = rotate90(current);
        }
    return forms; 
}

static int netArea(Net net) {
    int area = 0;
    for(List<Character> row : net) {
        for (char c:row) {
            if (c == '#') {
                area ++;
            }
        }
    }
    return area;
}

static boolean fits(Board board, Net net, int startX, int startY) { 
        for (int y = 0; y < net.size(); y++) {
            for (int x = 0; x < net.get(0).size(); x++) {
                if (net.get(y).get(x) != '#') {
                    continue;
                }
                int boardX = startX + x;
                int boardY = startY + y;

                if (boardY >= board.size() || boardX >= board.get(0).size()) {
                    return false;
                }
                if (board.get(boardY).get(boardX) > 0) {
                    return false;
                }
            }
        }
    return true; 
}

static void place_piece(Board board, Net net, int startX, int startY) {
    for (int y = 0; y < net.size(); y++) {
        for (int x = 0; x < net.get(0).size(); x++) {
            if (net.get(y).get(x) == '#') {
                int current = board.get(startY + y).get(startX + x);
                board.get(startY + y).set(startX + x, current + 1);
            }
        }
    }
}

static void remove_piece(Board board, Net net, int startX, int startY) {
    for (int y = 0; y < net.size(); y++) {
        for (int x = 0; x < net.get(0).size(); x++) {
            if (net.get(y).get(x) == '#') {
                int current = board.get(startY + y).get(startX + x);
                board.get(startY + y).set(startX + x, current - 1);
            }
        }
    }
}

static boolean solve(Board board, List<List<Net>> netsWithRotations, int[] counts, long[] nodesExplored, long nodeLimit) {
    if (nodesExplored[0] > nodeLimit) {
        return false;
    }
    if (allCountsZero(counts)) {
        return true;
    }
    for (int pieceIndex = 0; pieceIndex < netsWithRotations.size(); pieceIndex++) {
        if (counts[pieceIndex] == 0) {
            continue;
        }  
        for (Net net : netsWithRotations.get(pieceIndex)) {
            for (int y = 0; y < board.size(); y++) {
                for (int x = 0; x < board.get(0).size(); x++) {
                    nodesExplored[0]++;
                    if (nodesExplored[0] > nodeLimit) {
                        return false;
                    }
                    if (!fits(board, net, x, y)) {
                        continue;
                    }
                    place_piece(board, net, x, y);
                    counts[pieceIndex] -= 1;

                    if (solve(board, netsWithRotations, counts, nodesExplored, nodeLimit)) {
                        return true;
                    }
                    counts[pieceIndex] += 1;
                    remove_piece(board, net, x, y);
                }
            }
        } 
    }
    return false;
}

static ParsedInput parseInput(String path) throws IOException { 
    BufferedReader br = new BufferedReader(new FileReader(path));
    List<Net> nets = new ArrayList<>();
    List<Puzzle> puzzles = new ArrayList<>();
    List<String> lines = new ArrayList<>();
    String line;

    while ((line = br.readLine()) != null) {
        lines.add(line);
    }
    br.close();

    int i = 0;
    while (i < lines.size()) {
        line = lines.get(i).trim();
        if (line.isEmpty()) {
            i++;
            continue;
        }
        //net header
        if (line.endsWith(":") && line.substring(0, line.length() - 1).matches("\\d+")) {
            Net net = new Net();
            i++;

            while ( i < lines.size()) {
                String nextLine = lines.get(i).trim();
                if (nextLine.isEmpty()) {
                    i++;
                    break;
                }
                if (nextLine.matches("[#.]+")) {
                    List<Character> row = new ArrayList<>();
                    for (char c : nextLine.toCharArray()) {
                        row.add(c);
                    }
                    net.add(row);
                    i++;
                } else {
                    break;
                }
            }
            if (!net.isEmpty()) {
                nets.add(net);
            }
            continue;
        }
        //puzzle line with width x height: counts...
        int colonPos = line.indexOf(':');

        if (colonPos != -1) {
            String dimsPart = line.substring(0, colonPos).trim();
            String rest = line.substring(colonPos + 1).trim();
            int xPos  = dimsPart.indexOf('x');

            if (xPos != -1) {
                try {
                    int width = Integer.parseInt(dimsPart.substring(0, xPos).trim());
                    int height = Integer.parseInt(dimsPart.substring(xPos + 1).trim());
                    String[] parts = rest.split("\\s+");
                    int[] requirements = new int[parts.length];

                    for (int j = 0; j < parts.length; j++) {
                        requirements[j] = Integer.parseInt(parts[j]);
                    }
                    puzzles.add(new Puzzle(width, height, requirements));
                } catch (NumberFormatException e) {
                    System.out.println("Malformed puzzle line");
                }
            }
        }
        i++;
    }
    return new ParsedInput(nets, puzzles);
}


public static void main(String[] args) throws IOException {
    String path = "quest12/input.txt";
    int counter = 0;
    //have to split this into three lines, not like rust... let (nets, puzzles) = parse_input(path);
    ParsedInput parsed = parseInput(path);
    List<Net> nets = parsed.nets;
    List<Puzzle> puzzles = parsed.puzzles;

    if (nets.isEmpty()) {
        System.out.println("There are no nets in the input.txt file");
        return;
        }

    if (puzzles.isEmpty()) {
        System.out.println("There are no puzzels in the input.txt file");
        return;
        }

    List<List<Net>> netsWithRotations = new ArrayList<>();
    for (Net net : nets) {
        netsWithRotations.add(generateRotations(net));
        }

    List<Integer> netAreas = new ArrayList<>();
    for (Net net : nets) {
        netAreas.add(netArea(net));
        }

    long nodeLimit = 55_000_000L;
    Duration timeLimit = Duration.ofSeconds(10); 

    for (int puzzleIndex = 0; puzzleIndex < puzzles.size(); puzzleIndex++) {
        Puzzle puzzle = puzzles.get(puzzleIndex);
        int boardArea = puzzle.width * puzzle.height;
        int requiredArea = 0;

        for (int i = 0; i < puzzle.requirements.length; i++) {
            if (i >= netAreas.size()) {
                throw new RuntimeException("Puzzle requires net index " + i + " but only " + netAreas.size() + " nets were parsed");
                }
                requiredArea += puzzle.requirements[i] * netAreas.get(i);
            }
            System.out.println("Puzzle " + puzzle.width + "x" + puzzle.height + " - required area: " + requiredArea + ", board area: " + boardArea);

            if (requiredArea > boardArea) {
                System.out.println("No solution for " + puzzle.width + "x" + puzzle.height + " (pieces require more area than the board)");
            System.out.println();
            continue;
            }
        Board board = new Board();

        for (int y = 0; y < puzzle.height; y++) {
            List<Integer> row = new ArrayList<>();
            for (int x = 0; x < puzzle.width; x++) {
                row.add(0);
                }
            board.add(row);
            }
            int[] counts = puzzle.requirements.clone();
            long[] nodesExplored = new long[] { 0 };
            Instant start = Instant.now();

            boolean solved = solve(board, netsWithRotations, counts, nodesExplored, nodeLimit);
            Duration elapsed = Duration.between(start, Instant.now());

            if (solved) {
                counter++;

                System.out.println("Solved " + puzzle.width + "x" + puzzle.height + " in " + elapsed + ", nodes explored: " + nodesExplored[0]);
                for (List<Integer> row : board) {
                    for (int cell : row) {
                        if (cell > 0) {
                            System.out.print("#");
                        }
                        else {
                            System.out.print(".");
                        }
                    }
                System.out.println();
                }
            } else {
                if (nodesExplored[0] > nodeLimit || elapsed.compareTo(timeLimit) > 0) {
                    System.out.println("Stopped search for " + puzzle.width + "x" + puzzle.height + " (limit reached), nodes explored: " + nodesExplored[0] + ", time: " + elapsed);
                } else {
                    System.out.println("No solution found for " + puzzle.width + "x" + puzzle.height + " (exhaustive within limits), nodes explored" + nodesExplored[0] + ", time: " + elapsed);
                }
            }
            System.out.println();
        }
        System.out.println("Total amount of solved puzzles: " + counter);
    }
}   
