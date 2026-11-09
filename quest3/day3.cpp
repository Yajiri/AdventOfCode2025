#include <iostream>
#include <string>
#include <fstream>

//this allowes me to remove std:: from other places in the code, such as std::string, which becomes string
using namespace std;

int main() {
    int largest = 0;
    int secondLargest = 0;
    int startIndex = 0;
    string stringOfNumbers;

    ifstream file("input.txt");

    if (!file) {
        cout << "This file can't be found";
        return 1;
    }

    long long total = 0;
    long long len = stringOfNumbers.length();

    while (getline(file, stringOfNumbers)) {
        long long largest = 0;
        long long secondLargest = 0;
        int startIndex = 0;

        int len = stringOfNumbers.length();

    for (int i = 0;  i < len -1; i++) {
        if (stringOfNumbers[i] == '9') {
            largest = 9;
            startIndex = i + 1;
            break;
        }
        if (stringOfNumbers[i] - '0' > largest) {
            largest = stringOfNumbers[i] - '0';
            startIndex = i + 1;
        }
    }
    for (int i = startIndex; i < len; i++) {
        if (stringOfNumbers[i] - '0' > secondLargest) {
            secondLargest = stringOfNumbers[i] - '0';
        }
    }
        total += largest * 10 + secondLargest;
        }

    cout << "The largest possible number is: "
         << total
         << endl;
}