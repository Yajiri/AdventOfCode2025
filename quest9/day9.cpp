#include <vector>
#include <cmath>
#include <iostream>
#include <string>
#include <fstream>


using namespace std;

struct Grid {
    long long row;
    long long col;
};

int main() {
    ifstream file("input.txt");

    if(!file) {
        cout << "Could not open or find file";
        return 1;
    }

    vector<Grid> grid;

    string line;

    while (getline(file, line)) {
        size_t comPos = line.find(",");
        long long red_tile_row = stoll(line.substr(0, comPos));  //stoll for long, stoi for int.
        long long red_tile_col = stoll(line.substr(comPos + 1));
        grid.push_back({red_tile_row, red_tile_col});
    }

    long long largest = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = i + 1; j < grid.size(); j++) {
            long long dx = abs(grid[i].row - grid[j].row) + 1;
            long long dy = abs(grid[i].col - grid[j].col) + 1;
            long long area = dx * dy;
            if (area > largest) {
                largest = area;
            }
        }
    }
    cout << "The largest grid has an area of: " << largest;
}