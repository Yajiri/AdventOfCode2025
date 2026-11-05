#include <vector> 
#include <utility>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    vector<vector<int>> grid;

    while(true) {

        cout << "Please enter the numbers split by spaces (write done when done): ";

        string line;
        getline(cin, line);

        for (char &c : line) {
            c = toupper(c);
        }

        if (line == "DONE") {
            break;
        }

        stringstream ss(line);

        vector<int> row;
        int number;

        while (ss >> number) {
            row.push_back(number);
        }
    grid.push_back(row);
    }

    cout << "Please enter the operators split by spaces: ";
    string operators;
    getline(cin, operators);

    stringstream ss(operators);

    vector<char> ops;
    char op;

    while (ss >> op) {
        ops.push_back(op);
    }

    for (int col = 0; col < ops.size(); col++) {
        if (ops[col] == '*') {
            int result = 1;
            //you can just do "auto row" but the "const" makes sure it's not copying each row.
            for (const auto& row : grid) {
                result *= row[col];
            }
        //Just looks better to have the fist column be column 1 and not column 0, then keep it consisten so we don't have 2 column 1. 
        cout << "The value of column " << col + 1 << " is " << result <<"\n";
        }
        else if (ops[col] == '+') {
            int result = 0;
            for (const auto& row : grid) {
                result += row[col];
            }
        cout << "The value of column " << col + 1 << " is " << result <<"\n";
        }
        if (ops[col] == '/'){
            int result = grid[0][col];
            for (int row = 1; row < grid.size(); row++) {
                result /= grid[row][col];
            }
        cout << "The value of column " << col + 1 << " is " << result <<"\n";
        }
        if (ops[col] == '-') {
            int result = grid[0][col];
            for (int row = 1; row < grid.size(); row++) {
                result -= grid[row][col];
            }
        cout << "The value of column " << col + 1 << " is " << result << "\n";
        }
    }
}