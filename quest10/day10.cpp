#include <iostream>
#include <vector>
#include <climits>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>


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
    //need to implement the grids...
    ifstream file("input.txt");
    if(!file) {
        cout << "file can't be found";
        return 1;
    }

    vector<vector<int>> targets; 
    vector<vector<vector<int>>> all_buttons;
    string line;

    while (getline(file, line)) {
            //target
            regex targetPattern(R"(\[([.#]+)\])");
            smatch targetMatch;

            if (regex_search(line, targetMatch, targetPattern)) {
                vector<int> target;
                string targetStr = targetMatch[1];

                for (char c : targetStr) {
                    if (c == '#') {
                        target.push_back(1);
                    } else {
                        target.push_back(0);
                    }
                }
                targets.push_back(target);
            }

            vector<vector<int>> machineButtons;
            regex buttonPattern(R"(\((.*?)\))");

            for (sregex_iterator it(line.begin(), line.end(), buttonPattern);
                it != sregex_iterator();
                    ++it) {

            vector<int> button;
            string buttonStr = (*it)[1];
            stringstream ss(buttonStr);
            string number;

            while (getline(ss, number, ',')) {
                button.push_back(stoi(number));
            }
        machineButtons.push_back(button);
    }
    all_buttons.push_back(machineButtons);
}

    int total_value = 0;

    for (int i = 0; i < targets.size(); ++i) {
        int best = solve_and_return_best(targets[i], all_buttons[i]);
        cout << "Minimum amount of presses = " << best << "\n";
        total_value += best;
    }
    cout << "The total amount of presses required to reach the end point is at lease " << total_value;
}