#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct Range {
    int start;
    int end;
};

struct Range ranges[] = {
            {3,5},
            {10,14},
            {16,20},
            {12,18}
};

int main(void) {
    char line[100];
    int numbers[100];
    int count = 0;
    /*So this is confusing but an int takes up 4 bytes and each ranges contains a start and end so 8 byte, and thus since there are 4 elements in my current Range it 
    4 * 8 = 32 bytes of memory. 
    To sizeof(ranges) would return 32 and sizeof(ranges[0]) returns the value of the first range so 8. 
    So the sizeof(ranges) / sizeof(ranges[o]) = 32 / 8 = 4. This works because we have 4 elements in ranges.
    So why not just use for ( int j = 0; j < 4; j++) but this would fail based on the fact that if we add a fith element then... 
    keep in mind that the ranges are array based so range[0] = {3,5}, ranges[1] = {10,14} etc.
    */
    int rangeCount = sizeof(ranges) / sizeof(ranges[0]);


    printf("Please enter the numbers separated by space: ");
    fgets(line, sizeof(line),stdin);

    //So this will look for the first " " in the string, and then points to is.
    char *token = strtok(line, " ");
    //numbers[count++] = atoi(token); This appends the number to my array.
    //token = strtok(NULL, " "); will make it move to the next " " and so on.
    while (token != NULL) {
        numbers[count++] = atoi(token);
        token = strtok(NULL, " ");
    }

    for (int i = 0; i < count; i++) {
        int number = numbers[i];
        //Bool is not native to C...
        bool fresh = false;
        for (int j = 0; j < rangeCount; j++){
            if (number >= ranges[j].start && number <= ranges[j].end) {
            fresh = true;
            break;
            }
        }
        //In C you don't need the "== true", since fresh already is a boolean.
    if (fresh) {
        printf("%d is fresh\n", number);
    } else {
        printf("%d is not fresh\n", number);
        }
    }
    return 0;
}