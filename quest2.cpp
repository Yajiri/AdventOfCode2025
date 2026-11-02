#include <vector>
#include <utility>

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

std::vector<std::pair<int,int>> ranges {
    {11,22},
    {95,115},
    {998,1012},
    {1188511880,1188511890},
    {222220,222224},
    {1698522,1698528},
    {38593856,38593862}
};