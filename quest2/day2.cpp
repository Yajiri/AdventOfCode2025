#include <vector>
#include <utility>
#include <iostream>
#include <string>

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
int main() {

    std::vector<std::pair<int,int>> ranges {
        {11,22},
        {95,115},
        {998,1012},
        {1188511880,1188511890},
        {222220,222224},
        {446443,446449},
        {1698522,1698528},
        {38593856,38593862}
    };

    int invalidNumberValue = 0;

    for (const auto& [start, end] : ranges) {
        for (int n = start; n <= end; n++) {
            std::string s = std::to_string(n);
            if (s.length() % 2 == 0) {
                int half = s.length() / 2;

                std::string firstHalf = s.substr(0, half);
                std::string secondHalf = s.substr(half);

                if (firstHalf == secondHalf) {
                    std::cout << n << '\n';
                    invalidNumberValue = invalidNumberValue + n;
                }
            }
        }
    }
    std::cout << "Sum: " << invalidNumberValue;
}