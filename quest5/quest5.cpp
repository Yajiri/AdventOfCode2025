#include <vector> 
#include <utility>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    vector<pair<int,int>> ranges {
        {3,5},
        {10,14},
        {16,20},
        {12,18}
    };

    vector<int> numbers;
    int number;

    cout << "Please enter numbers separated by spaces: ";
    
    string line;
    getline(cin, line);

    stringstream ss(line);

    while (ss >> number) {
        numbers.push_back(number);
    }
    for (int number : numbers) {
        bool fresh = false;
        for (auto range : ranges) {
            if (number >= range.first && number <= range.second){
            fresh = true;
            break;
            }
        }
        if (fresh == true){
            cout << number
                 << "is fresh!\n";
        } else {
            cout << number
                 << "is not fresh!\n";
        }    
    }
}