#include <vector>
#include <string> 
#include <iostream>

using namespace std;

int main() {
    vector<string> grid = {
        "..@@.@@@@.",
        "@@@.@.@.@@",
        "@@@@@.@.@@",
        "@.@@@@..@.",
        "@@.@@@@.@@",
        ".@@@@@@@.@",
        ".@.@.@.@@@",
        "@.@@@.@@@@",
        ".@@@@@@@@.",
        "@.@.@@@.@."      
    };

    int rows = grid.size();
    int cols = grid[0].size();

    int dr[] = {-1,-1,-1,0,0,1,1,1};
    int dc[] = {-1,0,1,-1,1,-1,0,1}; 

    int count = 0;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {

            if(grid[r][c] != '@')
                continue;
            
                int neighbors = 0;

                for (int i = 0; i < 8; i++) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];

                    if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] == '@') {
                        neighbors++;
                    }
                }
            bool removable = neighbors < 4;
            if (removable) {
                count++;
                cout << "(" << r << "," << c << ") can be removed\n";
            }
        }
    }
    cout << count << " can be removed\n";
}