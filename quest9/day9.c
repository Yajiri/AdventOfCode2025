#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Grid {
    long long red_tile_row;
    long long red_tile_col;
};

int main(void) {
    FILE *file = fopen("input.txt", "r");
    char line[1000];
    long long largest = 0;
    int gridCount = 0;
    struct Grid grid[1000];
    int gridSize = sizeof(grid) / sizeof(grid[0]);

    if (file == NULL) {
        printf("The file can't be read");
        return 1;
    }

    while (fgets(line, sizeof(line), file)) {
    sscanf(line, "%lld,%lld",
            &grid[gridCount].red_tile_row,
            &grid[gridCount].red_tile_col);
            gridCount++;
        }
    fclose(file);

    for (int i = 0; i < gridCount; i++) {
        for (int j = i + 1; j < gridCount; j++) {
            long long dx = abs(grid[i].red_tile_row - grid[j].red_tile_row) + 1;
            long long dy = abs(grid[i].red_tile_col - grid[j].red_tile_col) + 1;
            long long area = dx * dy;

            if (area > largest) {
                largest = area;
            }
        }
    }
    printf("The area of the largest grid is: %lld", largest);
}