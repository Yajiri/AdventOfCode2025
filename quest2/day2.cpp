#include <vector>
#include <utility>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

/*can be done as this
struct Range {
    int start;
    int end;
};

std::vector<Range> ranges {
    {11,22},
    {95,115},
    {998,1012}
};
*/
//but there's a super command that combines them...

using namespace std;
int main() {

    std::ifstream file("input.txt");

    if (!file) {
        cout << "This file can't be read!";
        return 1;
    }

    string line;
    getline(file, line);

    vector<pair<long long, long long>> ranges;
    stringstream ss(line);
    string token;

    while (getline(ss, token, ',')) {
        size_t dashPos = token.find('-');

        long long start = stoll(token.substr(0, dashPos));
        long long end = stoll(token.substr(dashPos + 1));

        ranges.push_back({start, end});
    }

    long long invalidNumberValue = 0;

    for (const auto& [start, end] : ranges) {
        for (long long n = start; n <= end; n++) {
            string s = to_string(n);
            if (s.length() % 2 == 0) {
                int half = static_cast<int>(s.length()) / 2;

                string firstHalf = s.substr(0, half);
                string secondHalf = s.substr(half);

                if (firstHalf == secondHalf) {
                    cout << n << '\n';
                    invalidNumberValue += n;
                }
            }
        }
    }
    cout << "Sum: " << invalidNumberValue;
}