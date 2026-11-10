#include <vector> 
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main() {
    vector<vector<long long>> numbers;
    vector<char> operators;
    vector<string> lines; 
    long long finalResult = 0;

    ifstream file("input.txt");
    if(!file) {
        cout << "This file can't be read!";
        return 1;
    }

    string line;

    while(getline(file, line)) {
        lines.push_back(line);
    }

    stringstream opStream(lines.back());
    char op;

    while (opStream >> op) {
        operators.push_back(op);
    }

    for (size_t i = 0; i < lines.size() - 1; i++) {
        vector<long long> row;
        stringstream ss(lines[i]);
        
        long long num;

        while (ss >> num) {
            row.push_back(num);
        }
    
        numbers.push_back(row);
    }
    int cols = operators.size();

    for (int col = 0; col < cols; col++) {
        if (operators[col] == '*') {
            long long result = 1;
            //you can just do "auto row" but the "const" makes sure it's not copying each row.
            for (const auto& row : numbers) {
                result *= row[col];
            }
        finalResult += result;
        }
        else if (operators[col] == '+') {
            long long result = 0;
            for (const auto& row : numbers) {
                result += row[col];
            }
        finalResult += result;
        }
        if (operators[col] == '/'){
            long long result = numbers[0][col];
            for (int row = 1; row < numbers.size(); row++) {
                result /= numbers[row][col];
            }
        finalResult += result;
        }
        if (operators[col] == '-') {
            long long result = numbers[0][col];
            for (int row = 1; row < numbers.size(); row++) {
                result -= numbers[row][col];
            }
        finalResult += result;
        }
    }
    cout << "The final result is " << finalResult;
    return 0;
}