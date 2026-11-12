package quest8;

import java.io.*;
import java.util.*;

public class Oop8 {

    public static void main(String[] args) throws IOException {
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

        System.out.println(Solutions.solution(points));

        System.out.println(Solutions.solution(points));
    }
}