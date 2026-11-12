#include <string.h> 
#include <stdio.h>
#include <stdbool.h>

#define MAX_ROWS 200
#define MAX_COLS 1000
#define MAX_Line 1000


int main(void) {
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("Could not open file\n");
        return 1;
    }

    char grid[MAX_ROWS][MAX_COLS];
    int rows = 0;
    int cols = 0;
    int count = 0;
    char line[MAX_COLS];

    while (fgets(line, sizeof(line), fp) != NULL) {
        line[strcspn(line, "\n")] = '\0';

        strcpy(grid[rows], line);

        cols = strlen(line);
        rows++;
    }
    fclose(fp);

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