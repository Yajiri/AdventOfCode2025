#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ROWS 10
#define MAX_COLS 1000
#define MAX_LINE 10000

int main(void) {
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("Could not open file\n");
        return 1;
    }

    long long numbers[MAX_ROWS][MAX_COLS];
    char operators[MAX_COLS];
    char lines[MAX_ROWS + 1][MAX_LINE];
    int line_count = 0;

    while (fgets(lines[line_count], MAX_LINE, fp)) {
        lines[line_count][strcspn(lines[line_count], "\n")] = '\0';
        line_count++;
    }
    fclose(fp);

    int opCount = 0;

    char *token = strtok(lines[line_count - 1], " ");

    while (token != NULL) {
        operators[opCount++] = token[0];
        token = strtok(NULL, " ");
    }

    int rows = line_count -1;
    int cols = 0;
    long long finalResult = 0;

    for (int r = 0; r < rows; r++) {
        char *token = strtok(lines[r], " ");
        int c = 0;

        while (token != NULL) {
            numbers[r][c] = atoll(token);
            c++;
            token = strtok(NULL, " ");
        }

        if(r == 0)
            cols =c;
    }

        for (int col = 0; col < cols; col++) {
            if(operators[col] == '*') {
                long long result = 1;

                for (int row = 0; row < rows; row++) {
                    result *= numbers[row][col];
                }
                finalResult += result;
                //printf("Column %d = %d\n", col + 1, result);
            }

            else if(operators[col] == '+') {
                long long result = 0;

                for (int row = 0; row < rows; row++) {
                    result += numbers[row][col];
                }
                finalResult += result;
            //printf("Column %d = %d\n", col + 1, result);
            }

            else if (operators[col] == '-') {
                long long result = numbers[0][col];

                for (int x = 1; x < rows; x++) {
                    result -= numbers[x][col];
                }
                finalResult += result;
            //printf("Column %d = %d\n", col + 1, result);
            }
            else if (operators[col] == '/') {
                long long result = numbers[0][col];

                for (int x = 1; x < rows; x++){
                    result /= numbers[x][col];
                }
                finalResult += result;
            //printf("Column %d = %d\n", col + 1, result);
        }
    }
    printf("The final result is: %lld", finalResult);
    return 0;
}
