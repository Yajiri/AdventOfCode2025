#include <vector>
#include <string> 
#include <iostream>

using namespace std;

int main() {
    vector<string> grid = {
    ".......S.......",
    "...............",
    ".......^.......",
    "...............",
    "......^.^......",
    "...............",
    ".....^.^.^.....",
    "...............",
    "....^.^...^....",
    "...............",
    "...^.^...^.^...",
    "...............",
    "..^...^.....^..",
    "...............",
    ".^.^.^.^.^...^.",
    "..............."     
    };

    int rows = grid.size();
    int cols = grid[0].size();

    int count = 0;

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