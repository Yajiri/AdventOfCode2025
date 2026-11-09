#include <string.h> 
#include <stdio.h>
#include <stdbool.h>

#define MAX_ROWS 1000
#define MAX_COLS 1000


int main(void) {

    char grid[MAX_ROWS][MAX_COLS];

    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Could not open input.txt\n");
        return 1;
    }
    
    int rows = 0;

    while (fgets(grid[rows], MAX_COLS, file)) {
        grid[rows][strcspn(grid[rows], "\n")] = '\0';
        rows++;
    }

    fclose(file);

    int cols = strlen(grid[0]);

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

        //checks in the order top-left, top, top-right, left, right, bottom-left, bottom, bottom-right.
        for (int i = 0; i < 8; i++) {
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