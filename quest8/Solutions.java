package quest8;

import java.io.*;
import java.util.*;

public class Solutions {

static ArrayList<int[]> readInput() throws IOException {
    ArrayList<int[]> points = new ArrayList<>();
    BufferedReader br = new BufferedReader(
    new FileReader("quest8/input.txt"));

        String line;

        while ((line = br.readLine()) != null) {
            String[] parts = line.split(",");

            points.add(new int[] {
            Integer.parseInt(parts[0]),
            Integer.parseInt(parts[1]),
            Integer.parseInt(parts[2])
            });
        }

        br.close();
        return points;
}

static long dist2(int[] a, int[] b) {
long dx = a[0] - b[0];
long dy = a[1] - b[1];
long dz = a[2] - b[2];

return dx * dx + dy * dy + dz * dz;
}

static ArrayList<Pair> getShortest1000(ArrayList<int[]> points) {
        ArrayList<Pair> pairs = new ArrayList<>();
        for(int i = 0; i < points.size(); i++) {
            for (int j = i + 1; j < points.size(); j++){
                long d = dist2(points.get(i), points.get(j));
                pairs.add(new Pair(d, i, j));
                }
            }

            pairs.sort(Comparator.comparingLong(p -> p.distance));
            for (int k = 0; k < 1000; k++) {
            Pair p = pairs.get(k);

            System.out.println(
            points.get(p.i)[0] + "," + points.get(p.i)[1] + "," + points.get(p.i)[2]
            + " <-> " +
            points.get(p.j)[0] + "," + points.get(p.j)[1] + "," + points.get(p.j)[2]
            + " distance² = " + p.distance);
        }
    return new ArrayList<>(pairs.subList(0, 1000));
    }


static int solution() throws IOException {
        ArrayList<int[]> points = readInput();
        HashSet<Integer> visited = new HashSet<>();
        ArrayList<Integer> sizes = new ArrayList<>();
        ArrayList<Pair> pairs = new ArrayList<>();
        ArrayList<Integer>[] graph = new ArrayList[points.size()];
        pairs = getShortest1000(points);

        for (int i = 0; i < points.size(); i++) {
            graph[i] = new ArrayList<>();
            }

        for (Pair p : pairs) {
            graph[p.i].add(p.j);
            graph[p.j].add(p.i);
        }

        for (int start = 0; start < points.size(); start++) {
            if (visited.contains(start)) {
                continue;
            }
            Stack<Integer> stack = new Stack<>();
            stack.push(start);

            int size = 0;

            while(!stack.isEmpty()) {
                int node = stack.pop();
                if(visited.contains(node)) {
                    continue;
                }
                visited.add(node);
                size++;

                for (int neighbor : graph[node]) {
                    if(!visited.contains(neighbor)){
                        stack.push(neighbor);
                    }
                }
            }
        sizes.add(size);
        }
    sizes.sort(Collections.reverseOrder());
    return sizes.get(0) * sizes.get(1) * sizes.get(2);
    } 
}
