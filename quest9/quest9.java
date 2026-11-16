package quest9;

record Grid(int red_tile_row, int red_tile_col) {}

public class quest9 {

    public static void main(String[] args) {
        Grid[] grid = {
            new Grid(7, 1),
            new Grid(11, 1),
            new Grid(11,7),
            new Grid(9,7),
            new Grid(9,5),
            new Grid(2,5),
            new Grid(2,3),
            new Grid(7,3)            
        };

        int largest = 0;
        for (int i = 0; i < grid.length; i++) {
            for (int j = i + 1; j < grid.length; j++) {
                int dx = Math.abs(grid[i].red_tile_row() - grid[j].red_tile_row()) + 1;
                int dy = Math.abs(grid[i].red_tile_col() - grid[j].red_tile_col()) + 1; 

                int area = dx * dy;
                if (area > largest) {
                    largest = area;
                }
            }
        }
        System.out.println("The largest area of a gird is: " + largest);
    }
}