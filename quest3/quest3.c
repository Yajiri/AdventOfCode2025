#include <stdio.h>
#include <string.h>

int main(void) {
    int largest = 0;
    int secondLargest = 0;
    int startIndex = 0;
    char stringOfNumbers[100] = "";

    printf("Please enter the number sequence: ");
    //Ensure that the "%99" is correctly imputed otherwise there won't be any len later and that will ensure that the loops never run.
    scanf("%99s", stringOfNumbers);

    //do This once here instead, if you call the strlen inside the setup for the loop then it recalculates the lenght for each itteration of said loop 
    //and that does matter when the string is longer than in this case. Ensure that this is after the scanf...
    int len = strlen(stringOfNumbers);

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
    printf("The largest possible number is: %d%d", largest, secondLargest);
}