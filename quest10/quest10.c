#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_LIGHTS 10
#define MAX_BUTTONS 10


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
    int targets[3][MAX_LIGHTS] = {
    {0, 1, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 1, 1, 1, 0, 1}
};

int target_sizes[3] = {
    4,
    5,
    6
};
int all_buttons[3][MAX_BUTTONS][MAX_LIGHTS] = {

    /* Config 1 */
    {
        {3},
        {1, 3},
        {2},
        {2, 3},
        {0, 2},
        {0, 1}
    },

    /* Config 2 */
    {
        {0, 2, 3, 4},
        {2, 3},
        {0, 4},
        {0, 1, 2},
        {1, 2, 3, 4}
    },

    /* Config 3 */
    {
        {0, 1, 2, 3, 4},
        {0, 3, 4},
        {0, 1, 2, 4, 5},
        {1, 2}
    }
};
int button_sizes[3][MAX_BUTTONS] = {

    /* Config 1 */
    {1, 2, 1, 2, 2, 2},

    /* Config 2 */
    {4, 2, 2, 3, 4},

    /* Config 3 */
    {5, 3, 5, 2}
};
int button_counts[3] = {
    6,
    5,
    4
};
const char *names[3] = {
    "Config 1 [.##.]",
    "Config 2 [...#.]",
    "Config 3 [.###.#]"
};

int total_value = 0;

for (int i = 0; i < 3; i++) {
    int best = solve_and_return_best(targets[i], target_sizes[i], all_buttons[i], button_sizes[i], button_counts[i]);
        printf("%s - Minimum amount of presses is %d!\n", names[i], best);
        total_value += best;
    }
    printf("The least amount of presses required to reach the final state of all machines is %d!\n", total_value);
}
