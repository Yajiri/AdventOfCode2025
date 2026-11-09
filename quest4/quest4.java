package quest4;


public class quest4 {
    public static void main(String[] args){

        String[] grid = {
            "..@@.@@@@.",
            "@@@.@.@.@@",
            "@@@@@.@.@@",
            "@.@@@@..@.",
            "@@.@@@@.@@",
            ".@@@@@@@.@",
            ".@.@.@.@@@",
            "@.@@@.@@@@", 
            ".@@@@@@@@.",
            "@.@.@@@.@."
        };
    
    int rows = grid.length;
    int cols = grid[0].length();

    int[] dr = {-1,-1,-1,0,0,1,1,1};
    int[] dc = {-1,0,1,-1,1,-1,0,1};

    int count = 0;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {

            if (grid[r].charAt(c) != '@') {
                continue;
            }
        int neighbors = 0;

        for (int i = 0; i < 8; i++){
            int nr = r + dr[i];
            int nc = c + dc [i];

            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr].charAt(nc) == '@') {
                neighbors++;
                    }
                }
            boolean removable = neighbors < 4;
            if ( removable) {
                count++;
                System.out.println("(" + r + "," + c + ") can be removed");
                }
            }
        }
    System.out.println(count + " can be removed!");
    }
}