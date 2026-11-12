#include <vector>
#include <fstream> 
#include <iostream>
#include <string>

using namespace std;

int main() {
    int count = 0;
    vector<string> grid;

    ifstream file("input.txt");
    if(!file) {
        cout << "This file can't be found!";
        return 1;
    }

    string line;

    while(getline(file, line)) {
        grid.push_back(line);
    }

    int rows = grid.size();
    int cols = grid[0].size();

    for(int i = 0; i < cols; i++) {
        if (grid[0][i] == 'S') {
            cout << "The position of S is (0," << i << ")\n";
            grid[1][i] = '|';

            cout << grid[1] <<"\n";
            break;
        }
    }
    for (int r = 0; r < rows - 1; r++) {
        for (int c = 0; c < cols; c++) {
            if(grid[r][c] == '|') {
                if (grid[r+1][c] == '^') {
                    if (c > 0) {
                        grid[r+1][c-1] = '|';
                    } if (c + 1 < cols) {
                        grid[r+1][c+1] = '|';
                    }
                    count++;
                    continue;
                }
                else if (grid[r+1][c] == '.') {
                    grid[r+1][c] = '|';
                }
            }
        }
    }
    cout << count <<"\n";
}