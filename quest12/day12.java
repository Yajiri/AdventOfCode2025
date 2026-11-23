package quest12;
import java.io.*;
import java.util.*;
import java.nio.file.*;
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
    return false; 
}

static Net rotate90(Net net) { return null; }

static List<Net> generateRotations(Net net) {return null; }
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
    //to be implemented
    return false; }
static void place_piece(Board board, Net net, int startX, int startY) {
    //to be implemented
}
static void remove_piece(Board board, Net net, int startX, int startY) {
    //to be implemented
}
static boolean solve(Board board, List<List<Net>> netsWithRotations, int[] counts, long[] nodesExplored, long nodeLimit) {
    //to be implemented
    return false;
}
static ParsedInput parseInput(String path) throws IOException { 
    //to be implemented
    return null; 
}


public static void main(String[] args) throws IOException {
    }
}   
