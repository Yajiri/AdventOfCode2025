#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    long total = 0;
    char stringOfNumbers[1000] = "";

    FILE *file = fopen("input.txt", "r");

    if (file == NULL) {
        printf("Could not open file");
        return 1;
    };

    while (fgets(stringOfNumbers, sizeof(stringOfNumbers), file)) {
        //remove trailing new-line 
        stringOfNumbers[strcspn(stringOfNumbers, "\n")] = '\0'; 

        int len = strlen(stringOfNumbers);

        if (len == 0) {
            continue;
        }
        long largest = 0;
        long secondLargest = 0;
        int startIndex = 0;

    for (int i = 0; i < len - 1; i++) {
        if (stringOfNumbers[i] == '9'){
            largest = 9;
            startIndex = i + 1;
            break;
        }
        if (stringOfNumbers[i] - '0' > largest){
            largest = stringOfNumbers[i] - '0';
            startIndex = i + 1;
        }
    }
    for (int i = startIndex; i < len; i++) {
        if (stringOfNumbers[i] -'0' > secondLargest) {
            secondLargest = stringOfNumbers[i] -'0';
            }
        }
        total += largest * 10 + secondLargest;
    }
    printf("The largest possible number is: %d", total);
}