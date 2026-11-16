#include <vector>
#include <utility>
#include <cmath>
#include <iostream>

using namespace std;

int main() {
    vector<pair<int,int>> grid {
        {7,1},
        {11,1},
        {11,7},
        {9,7},
        {9,5},
        {2,5},
        {2,3},
        {7,3}
    };
    int largest = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = i + 1; j < grid.size(); j++) {
            int dx = abs(grid[i].first - grid[j].first) + 1;
            int dy = abs(grid[i].second - grid[j].second) + 1;
            int area = dx * dy;
            if (area > largest) {
                largest = area;
            }
        }
    }
    cout << "The largest grid has an area of: " << largest;
}