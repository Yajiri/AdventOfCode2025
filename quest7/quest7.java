package quest7;


public class quest7 {
    public static void main(String[] args){

        char[][] grid = {
            ".......S.......".toCharArray(),
            "...............".toCharArray(),
            ".......^.......".toCharArray(),
            "...............".toCharArray(),
            "......^.^......".toCharArray(),
            "...............".toCharArray(),
            ".....^.^.^.....".toCharArray(),
            "...............".toCharArray(),
            "....^.^...^....".toCharArray(),
            "...............".toCharArray(),
            "...^.^...^.^...".toCharArray(),
            "...............".toCharArray(),
            "..^...^.....^..".toCharArray(),
            "...............".toCharArray(),
            ".^.^.^.^.^...^.".toCharArray(),
            "...............".toCharArray()
        };
    
    int rows = grid.length;
    int cols = grid[0].length;

    int count = 0;

    for (int i = 0; i < cols; i++) {
        if(grid[0][i] == 'S') {
            System.out.println("The position in the grid is (0, " + i + ")");

            grid[1][i] = '|';

            System.out.println(new String(grid[1]));
            break;
            }
        }
        // - 1 is just to make sure we don't go outside the span either.
    for (int r = 1; r < rows - 1; r++){
        for (int c = 0; c < cols; c++){
            if (grid[r][c] == '|') {
                if (grid[r+1][c] == '^') {
                    /*The if statements is just to make sure nothing happens to get outside of the column span. 
                    Doesn't matter in this case but just future profing if someone wants to try another pattern*/
                    if (c > 0) {
                    grid[r+1][c-1] = '|';
                    } if (c + 1 < cols) {
                    grid[r+1][c+1] = '|';
                    }
                    count++;
                    continue;
                    } else if (grid[r+1][c] == '.') {
                        grid[r+1][c] = '|';
                    }
                }
            }
        }
    System.out.println(count);
    }
}