package quest8;
import java.util.*;

public class quest8{

static class Pair {
    long distance;
    int i;
    int j;

    Pair(long distance, int i, int j) {
        this.distance = distance;
        this.i = i;
        this.j = j;
    }
}
public static void main(String[] args) {
    int[][] points = {
        {162,817,812},
        {57,618,57},
        {906,360,560},
        {592,479,940},
        {352,342,300},
        {466,668,158},
        {542,29,236},
        {431,825,988},
        {739,650,466},
        {52,470,668},
        {216,146,977},
        {819,987,18},
        {117,168,530},
        {805,96,715},
        {346,949,466},
        {970,615,88},
        {941,993,340},
        {862,61,35},
        {984,92,344},
        {425,690,689}
        };
        System.out.println(solution(points));
    }

static long dist2(int[] a, int[] b) {
long dx = a[0] - b[0];
long dy = a[1] - b[1];
long dz = a[2] - b[2];

return dx * dx + dy * dy + dz * dz;
}

static ArrayList<Pair> getShortest10(int[][] points) {
        ArrayList<Pair> pairs = new ArrayList<>();
        for(int i = 0; i < points.length; i++) {
            for (int j = i + 1; j < points.length; j++){
                long d = dist2(points[i], points[j]);
                pairs.add(new Pair(d, i, j));
                }
            }

            pairs.sort(Comparator.comparingLong(p -> p.distance));
            for (int k = 0; k < 10; k++) {
            Pair p = pairs.get(k);

            System.out.println(
            points[p.i][0] + "," + points[p.i][1] + "," + points[p.i][2]
            + " <-> " +
            points[p.j][0] + "," + points[p.j][1] + "," + points[p.j][2]
            + " distance² = " + p.distance);
        }
    return new ArrayList<>(pairs.subList(0, 10));
    }
    
static int solution(int[][] points) {
        HashSet<Integer> visited = new HashSet<>();
        ArrayList<Integer> sizes = new ArrayList<>();
        ArrayList<Pair> pairs = new ArrayList<>();
        ArrayList<Integer>[] graph = new ArrayList[points.length];
        pairs = getShortest10(points);

        for (int i = 0; i < points.length; i++) {
            graph[i] = new ArrayList<>();
            }

        for (Pair p : pairs) {
            graph[p.i].add(p.j);
            graph[p.j].add(p.i);
        }

        for (int start = 0; start < points.length; start++) {
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