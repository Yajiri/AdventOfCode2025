#include <stdio.h>
#include <string.h>

struct Range {
    int start;
    int end;
};

struct Range ranges[] = {
    {11,22},
    {95,115},
    {998,1012},
    {1188511880,1188511890},
    {222220,222224},
    {446443,446449},
    {1698522,1698528},
    {38593856,38593862}
};

int main(void) {
    int invalidNumberValue = 0;
    int rangeCount = sizeof(ranges) / sizeof(ranges[0]);

    for (int i = 0; i < rangeCount; i++) {
        for (int n = ranges[i].start; n <= ranges[i].end; n++) {

            char s[20];
            sprintf(s, "%d", n);
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
                printf("%d\n", n);
                invalidNumberValue = invalidNumberValue + n;
            } 
        }
    }

    printf("Invalid count: %d\n", invalidNumberValue);
    return 0;
}