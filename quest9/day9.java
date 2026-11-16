package quest9;
import java.io.*;
import java.util.*;

record Grid(long red_tile_row, long red_tile_col) {}

public class day9 {

    public static void main(String[] args) throws IOException {
        long largest = 0;
        BufferedReader br = new BufferedReader(new FileReader("quest9/input.txt"));
        ArrayList<Grid> grid = new ArrayList<>();
        String line;

        while ((line = br.readLine()) != null) {
            line = line.trim();

            String[] parts = line.split(",");

            long red_tile_row = Long.parseLong(parts[0]);
            long red_tile_col = Long.parseLong(parts[1]);

            grid.add(new Grid(red_tile_row, red_tile_col));
        }

        for (int i = 0; i < grid.size(); i++) {
            for (int j = i + 1; j < grid.size(); j++) {
                long dx = Math.abs(grid.get(i).red_tile_row() - grid.get(j).red_tile_row()) + 1;
                long dy = Math.abs(grid.get(i).red_tile_col() - grid.get(j).red_tile_col()) + 1; 

                long area = dx * dy;
                if (area > largest) {
                    largest = area;
                }
            }
        }
        br.close();
        System.out.println("The largest area of a grid is: " + largest);
    }
}