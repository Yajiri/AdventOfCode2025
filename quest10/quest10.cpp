#include <iostream>
#include <vector>
#include <climits>

using namespace std;

//need to have const, const otherwise I get problems later on in the code. Because I can't bind a const vector to a non-const reference.
bool matches (const vector<int>&a, const vector<int>&b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) return false;
    } 
    return true;
}

int solve_and_return_best(const vector<int>&target, const vector<vector<int>>&buttons) {
    int best = INT_MAX;
    int combinations = 1 << buttons.size();

    for (int mask = 0; mask < combinations; ++mask) {
        vector<int> state(target.size(), 0);
        int presses = 0;

        for (size_t button = 0; button < buttons.size(); ++button) {
            if (mask &(1 << button)) {
                ++presses;
            
            for (int light : buttons[button]) {
                state[light] ^= 1;
                }
            }
        }
        if (matches(state, target)) {
            best = min(best, presses);
        } 
    }
    return best;
} 
int main() {
    vector<vector<int>> targets {
        {0, 1, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 1, 1, 0, 1}
    };
    vector<vector<vector<int>>> all_buttons {
        {
            {3},
            {1, 3},
            {2},
            {2, 3},
            {0, 2},
            {0,1}
        },
        {
            {0, 2, 3, 4},
            {2, 3},
            {0, 4},
            {0, 1, 2},
            {1, 2, 3, 4}
        },
        {
            {0, 1, 2, 3, 4},
            {0, 3, 4},
            {0, 1, 2, 4, 5},
            {1, 2}
        }
    };
    vector<string> names {
        "Config 1 [.##.]",
        "Config 2 [...#.]",
        "Config 3 [.###.#]"
    };

    int total_value = 0;

    for (int i = 0; i < targets.size(); ++i) {
        int best = solve_and_return_best(targets[i], all_buttons[i]);
        cout << names[i] << " - Minimum amount of presses = " << best << "\n";
        total_value += best;
    }
    cout << "The total amount of presses required to reach the end point is at lease " << total_value;
}