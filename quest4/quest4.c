#include <string.h>
#include <stdio.h>
#include <stdbool.h>

char grid[10][11] = {
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

int main(void) {
    int rows = sizeof(grid) / sizeof(grid[0]);
    int cols = sizeof(grid[0]) - 1; //removes the '\0'
    
    int dr[] = {-1,-1,-1,0,0,1,1,1};
    int dc[] = {-1,0,1,-1,1,-1,0,1}; 

    int count = 0;

    // we could also set them both to 10 since it's fixed in this case.
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {

            if (grid[r][c] != '@') {
                continue;
            }
        int neighbors = 0;

        for (int i = 0; i  < 8; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];

        
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] == '@') {
                neighbors++;
                }
            }
        bool removable = neighbors < 4;
        if (removable) {
            count++;
            printf("%d,%d can be removed\n", r, c);
            }
        }
    }
    printf("%d can be removed.", count);
    return 0;
}