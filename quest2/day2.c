#include <stdio.h>
#include <string.h>

struct Range {
    long long start;
    long long end;
};

int main(void) {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL ) {
        printf("The file can not be read!");
        return 1;
    }

    struct Range ranges[1000];
        int rangeCount = 0;

    char line[10000];
    
    fgets(line, sizeof(line), file);
    fclose(file);

    char *token = strtok(line, ",");

    while (token != NULL) {
        sscanf(token, "%lld-%lld",
                &ranges[rangeCount].start,
                &ranges[rangeCount].end);
        rangeCount++;
        token = strtok(NULL, ",");
    }

    long long invalidNumberValue = 0;

    for (int i = 0; i < rangeCount; i++) {
        for (long long n = ranges[i].start; n <= ranges[i].end; n++) {

            char s[32];
            sprintf(s, "%lld", n);

            int len = strlen(s);

            if (len % 2 != 0) {
                continue;
            }
            int half = len / 2;
            int match = 1;

            for (int j = 0; j < half; j++) {
                if (s[j] != s[j + half]) {
                    match = 0;
                    break;
                }
            }
            if (match) {
                printf("%lld\n", n);
                invalidNumberValue += n;
            } 
        }
    }

    printf("Invalid count: %lld\n", invalidNumberValue);
    return 0;
}