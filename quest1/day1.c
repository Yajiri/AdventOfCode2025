#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main(void) {

    int startPoint = 50;
    int x = 0;
    char command[10] = "";

    FILE *file = fopen("input.txt", "r");

    if (file == NULL) {
        printf("Could not open file");
        return 1;
    }

    while(fscanf(file, "%9s", command) == 1) {
        for (int i = 0; command[i] != '\0'; i++) {
            command[i] = toupper(command[i]);
        }

        char direction = command[0];
        int moveSteps;
        
        sscanf(command + 1, "%d", &moveSteps);

        if (direction == 'L') {
            startPoint = (startPoint + moveSteps) % 100;
            if (startPoint == 0) {
                x++;
            } 
        }
        if (direction == 'R') {
            startPoint = (startPoint - moveSteps) % 100;
            if (startPoint == 0) {
                x++;
            }
        }
    }
    fclose(file);
    printf("Stopped at 0: %d amount of times.\n", x);
    return 0;
}

