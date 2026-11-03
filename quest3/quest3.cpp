#include <iostream>
#include <string>

//this allowes me to remove std:: from other places in the code, such as std::string, which becomes string
using namespace std;

int main() {
    int largest = 0;
    int secondLargest = 0;
    int startIndex = 0;
    string stringOfNumbers;

    cout << "Please enter the number sequence: ";
    cin >> stringOfNumbers;

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
    cout << "The largest possible number is: "
         << largest
         << secondLargest
         << endl;
}