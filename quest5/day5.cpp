#include <vector>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Range {
    long long start;
    long long end;
};

int main() {
    ifstream file("input.txt");

    if(!file) {
        cout << "Could not open the file";
        return 1;
    }
    
    int totalFreshItems = 0;
    vector<Range> ranges;
    vector<long long> numbers;

    string line;
    bool readingRanges = true;

    while (getline(file, line)) {

        if (line.empty()) {
            readingRanges = false;
            continue;
        }
        if (readingRanges) {
            size_t dashPos = line.find('-');

            long long start = stoll(line.substr(0, dashPos));
            long long end = stoll(line.substr(dashPos + 1));

            ranges.push_back({start, end});
        } else {
            numbers.push_back(stoll(line));
        }
    }
    file.close();

    for (const auto& number : numbers) {
        bool fresh = false;
        for (auto range : ranges) {
            if (number >= range.start && number <= range.end){
            fresh = true;
            totalFreshItems++;
            break;
                }
            }
        /* if (fresh == true){
            cout << number
                 << "is fresh!\n";
        } else {
            cout << number
                 << "is not fresh!\n";
        } */   
    }
    cout << "The total amount of fresh items are: " << totalFreshItems;
}