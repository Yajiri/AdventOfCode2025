#include <iostream>
#include <string>

using namespace std;

int main() {
    int startPoint = 50;
    int x = 0;
    string command;

    while (true) {
        cout << "Enter command: ";
        cin >> command;

        //Converting the command to uppercase to ensure that it works with the later code
        for (char &c : command) {
            c = toupper(c);
        }

        if (command == "DONE") {
            break;
        }

        char direction = command[0];
        int moveSteps = stoi(command.substr(1));

        if (direction == "L") {
            startPoint = (startPoint + moveSteps) % 100;

            if (startPoint) {
                x++;
            }
        }

        if (direction == "R") {
            startPoint = (startPoint + moveSteps) % 100;

            if (startPoint == 0) {
                x++;
            }
        }
    }
    cout << "Stopped at 0 " << x << " times" << endl;

    return 0;
}