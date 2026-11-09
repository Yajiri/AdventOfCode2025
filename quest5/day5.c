#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct Range {
    long long start;
    long long end;
};


int main(void) {
    FILE *file = fopen("input.txt", "r");
    int freshItems = 0;
    bool readingRanges = true;
    char line[1000];
    long long numbers[1000];
    int count = 0;
    struct Range ranges[1000];
        int rangeCount = 0;

    if (file == NULL) {
        printf("The file can not be read");
        return 1;
    }

    while (fgets(line, sizeof(line), file)){
        if (line[0] == '\n') {
            readingRanges = false;
            continue;
        }

        if (readingRanges) {
            sscanf(line, "%lld-%lld",
                &ranges[rangeCount].start,
                &ranges[rangeCount].end);
                rangeCount++;
        } else {
            sscanf(line, "%lld", &numbers[count]);
            count++;
        }
    }
    fclose(file);

    for (int i = 0; i < count; i++) {
        long long number = numbers[i];
        for (int j = 0; j < rangeCount; j++){
            if (number >= ranges[j].start && number <= ranges[j].end) {
            freshItems++;
            break;
            }
        }
    }
    printf("Number of fresh items %d\n", freshItems);
    return 0;
}