#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
    
    int startPoint = 50;
    int x = 0;
    string command;

    ifstream file("input.txt");

    if (!file) {
        cout << "could not open file." << endl;
        return 1;
    }

    while (file >> command) {
        
        for (char &c : command) {
            c = toupper(c);
        }

        char direction = command[0];
        int moveSteps = stoi(command.substr(1));

        if (direction == 'L') {
            startPoint = (startPoint + moveSteps) % 100;

            if (startPoint == 0) {
                x++;
            }
        }

        if (direction == 'R') {
            startPoint = (startPoint - moveSteps + 100) % 100;

            if (startPoint == 0) {
                x++;
            }
        }
    }
    cout << "Stopped at 0 " << x << " times" << endl;

    return 0;
}