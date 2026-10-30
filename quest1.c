#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {

    int startPoint = 50;
    int x = 0;
    char command[10] = "";

    while(1) {
        printf("Command: ");
        scanf("%9s", command);
        for (int i = 0; command[i] != '\0'; i++){
            command[i] = toupper(command[i]);
        }

        if (strcmp(command, "DONE") == 0) {
            break;
        }
        char direction = command[0];
        int moveSteps;
        sscanf(command +1, "%d", &moveSteps);
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
    printf("Stopped at 0: %d amount of times.\n", x);
    return 0;
}

