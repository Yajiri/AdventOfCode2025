#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LIGHTS 100
#define MAX_BUTTONS 100
#define MAX_MACHINES 1000

int targets[MAX_MACHINES][MAX_LIGHTS];
int target_sizes[MAX_MACHINES];
    
int all_buttons[MAX_MACHINES][MAX_BUTTONS][MAX_LIGHTS];
int button_sizes[MAX_MACHINES][MAX_BUTTONS];
int button_counts[MAX_MACHINES];


bool matches (const int a[], const int b [], int size) {
    for(int i = 0; i < size; i++) {
        if(a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

int solve_and_return_best (int target[], int target_size, int buttons[][MAX_LIGHTS], int button_sizes[], int button_count) {
            int best = INT_MAX;
            int combinations = 1 << button_count;

            for (int mask = 0; mask < combinations; mask++) {
                int state[MAX_LIGHTS] = {0};
                int presses = 0;

                for (int button = 0; button < button_count; button++) {
                    if (mask & (1 << button)) {
                        presses++;
                        for (int light = 0; light < button_sizes[button]; light++) {
                            int light_index = buttons[button][light];
                            state[light_index] ^= 1;
                        }
                    }
                }
                if (matches(state, target, target_size)) {
                    if (presses < best) {
                        best = presses;
            }
        }

    }
    return best;
}

int main(void) {
    int machine_count = 0;

    FILE *file = fopen("input.txt", "r");
    char line[1000];    
    int total_value = 0;

    if (file == NULL) {
        printf("This file can't be read");
        return 1;
    }

    while (fgets(line, sizeof(line), file)) {
        char *start = strchr(line, '[');
        char *end = strchr(line, ']');
        int target_length = 0;

        if (start == NULL || end == NULL) {
            continue;
        }

        for (char *p = start + 1; p < end; p++) {
            if (*p == '#') {
                targets[machine_count][target_length] = 1;
            }else {
                targets[machine_count][target_length] = 0;
            }
            target_length++;
        }
        target_sizes[machine_count] = target_length;

        char *current = line;

        int current_button_count = 0;

        while ((current = strchr(current, '(')) != NULL) {

        current++;
        
        int button_length = 0;
        char number_buffer[16];
        int buffer_pos = 0;

        while (*current && *current != ')') {

            if (*current == ',') {

                number_buffer[buffer_pos] = '\0';

                all_buttons[machine_count]
                           [current_button_count]
                           [button_length++] =
                    atoi(number_buffer);

                buffer_pos = 0;
            }
            else {
                number_buffer[buffer_pos++] = *current;
            }
            current++;
        }

        number_buffer[buffer_pos] = '\0';

        all_buttons[machine_count]
                   [current_button_count]
                   [button_length++] =
            atoi(number_buffer);

        button_sizes[machine_count]
                    [current_button_count] =
            button_length;

        current_button_count++;
    }
    button_counts[machine_count] =
        current_button_count;
        machine_count++;
}
fclose(file);

for (int i = 0; i < machine_count; i++) {
    int best = solve_and_return_best(targets[i], target_sizes[i], all_buttons[i], button_sizes[i], button_counts[i]);
        printf("%d - Minimum amount of presses is %d!\n", i + 1, best);
        total_value += best;
    }
    printf("The least amount of presses required to reach the final state of all machines is %d!\n", total_value);
    return 0;
}