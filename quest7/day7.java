package quest7;

import java.io.*;
import java.util.*;


public class day7 {
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new FileReader("quest7/input.txt"));
        int count = 0;

        ArrayList<StringBuilder> grid = new ArrayList<>();
        String line;

        while ((line = br.readLine()) != null) {
                grid.add(new StringBuilder(line));
        }
        br.close();
        int rows = grid.size();
        int cols = grid.get(0).length();

    for (int i = 0; i < cols; i++) {
        if (grid.isEmpty()) {
        System.out.println("Input file is empty");
        return;
        }

        if(grid.get(0).charAt(i) == 'S') {
            System.out.println("The position in the grid is (0, " + i + ")");

            grid.get(1).setCharAt(i, '|');

            System.out.println(new String(grid.get(1)));
            break;
            }
        }
        // - 1 is just to make sure we don't go outside the span either.
    for (int r = 1; r < rows - 1; r++){
        for (int c = 0; c < cols; c++){
            if (grid.get(r).charAt(c) == '|') {
                if (grid.get(r+1).charAt(c) == '^') {
                    /*The if statements is just to make sure nothing happens to get outside of the column span. 
                    Doesn't matter in this case but just future profing if someone wants to try another pattern*/
                    if (c > 0) {
                    grid.get(r+1).setCharAt(c-1,'|');
                    } if (c + 1 < cols) {
                    grid.get(r+1).setCharAt(c+1, '|');
                    }
                    count++;
                    continue;
                    } else if (grid.get(r+1).charAt(c) == '.') {
                        grid.get(r+1).setCharAt(c, '|');
                    }
                }
            }
        }
    System.out.println(count);
    }
}