#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Grid {
    int red_tile_row;
    int red_tile_col;
};

struct Grid grid[] = {
    {7,1},
    {11,1},
    {11,7},
    {9,7},
    {9,5},
    {2,5},
    {2,3},
    {7,3}
};

int main(void) {
    int largest = 0;
    int gridSize = sizeof(grid) / sizeof(grid[0]);
    for (int i = 0; i < gridSize; i++) {
        for (int j = i + 1; j < gridSize; j++) {
            int dx = abs(grid[i].red_tile_row - grid[j].red_tile_row) + 1;
            int dy = abs(grid[i].red_tile_col - grid[j].red_tile_col) + 1;
            int area = dx * dy;

            if (area > largest) {
                largest = area;
            }
        }
    }
    printf("The area of the largest grid is: %d", largest);
}