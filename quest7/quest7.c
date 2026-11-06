#include <string.h> 
#include <stdio.h>
#include <stdbool.h>

char grid[][sizeof(".......S.......")] = {
    ".......S.......",
    "...............",
    ".......^.......",
    "...............",
    "......^.^......",
    "...............",
    ".....^.^.^.....",
    "...............",
    "....^.^...^....",
    "...............",
    "...^.^...^.^...",
    "...............",
    "..^...^.....^..",
    "...............",
    ".^.^.^.^.^...^.",
    "..............."
};

int main(void) {
    int rows = sizeof(grid) / sizeof(grid[0]);
    int cols = sizeof(grid[0]) - 1; //removes the '\0'

    int count = 0;

    for (int i = 0; i < cols; i++) {
        if(grid[0][i] == 'S') {
            printf("The position of the grid is (0,%d)", i);

            grid[1][i] = '|';

            printf("%s\n", grid[1]);
            break;
        }
    }
    
    for(int r = 1; r < rows - 1; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == '|') {
                if (grid[r+1][c] == '^') {
                    if (c > 0) {
                    grid[r+1][c-1] = '|';
                    } 
                    if (c + 1 < cols) {
                    grid[r+1][c+1] = '|';
                    }
                count++;
                continue;
                }
                else if (grid[r+1][c] == '.') {
                grid[r+1][c] = '|';
                }
            }
        }
    }
    printf("%d", count);
}