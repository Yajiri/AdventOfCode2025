#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_ROWS 100
#define MAX_COLS 100

int main(void) {
    int rows[MAX_ROWS][MAX_COLS];
    int rowCount = 0;
    int colCount = 0;

    char numbers[1000];
    char operators[100];

    while (1) {
        printf("Please enter the sequence of numbers split by spacing (line by line), when done type done:\n ");

        //reads and stores the input into my array of characters
        fgets(numbers, sizeof(numbers), stdin);

        //remove newline
        numbers[strcspn(numbers, "\n")] = '\0';

        //ensure that it works no matter if you write "done", "DONE" or some amalgamation.
        for (int j = 0; numbers[j] != '\0'; j++) {
            numbers[j] = toupper(numbers[j]);
            }
        if (strcmp(numbers, "DONE") == 0) {
            break;
        }
        
        int col = 0;
        char *token = strtok(numbers, " \t");
        
        while (token != NULL) {
            rows[rowCount][col] = atoi(token);
            col ++;

            token = strtok(NULL, " \t");
        }

        colCount = col;
        rowCount++;
    } 
        printf("Please enter the operators white spaces in between: ");
        fgets(operators, sizeof(operators), stdin);
        char *op = strtok(operators, " \t");
        char ops[MAX_COLS];
        int opCount = 0;

        while(op != NULL) {
            ops[opCount] = op[0];
            opCount++;

            op = strtok(NULL, " \t");
        }
        for (int col = 0; col < colCount; col++) {
            if(ops[col] == '*') {
                int result = 1;
                for (int row = 0; row < rowCount; row++ ) {
                    result = result * rows[row][col];
                }
            printf("The Value of the column is: %d in column %d\n", result, col);
            }
            if(ops[col] == '+') {
                int result = 0;
                for (int row = 0; row < rowCount; row++) {
                    result += rows[row][col];
                }
            printf("The Value of the column is: %d in column %d\n", result, col);
            }
            if (ops[col] == '-') {
                int result = rows[0][col];
                for (int x = 1; x < rowCount; x++) {
                    result -= rows[x][col];
                }
            printf("The Value of the column is: %d in column %d\n", result, col);
            }
            if (ops[col] == '/') {
                int result = rows[0][col];
                for (int x = 1; x < rowCount; x++){
                    result /= rows[x][col];
                }
            printf("The Value of the column is: %d in column %d\n", result, col);
            }
        }
        printf("\n");
    return 0;
}