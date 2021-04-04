#include <vector>
#include <unordered_map>
#include <math.h>
using namespace std;

class Solution
{
public:
    int numRabbits(vector<int> &answers)
    {
        unordered_map<int, int> ans2Cnts;
        for (auto answer : answers)
        {
            ++ans2Cnts[answer];
        }
        int res = 0;
        for (auto ans2Cnt : ans2Cnts)
        {
            res += ceil(ans2Cnt.second / ceil(ans2Cnt.first + 1)) * (ans2Cnt.first + 1);
        }
        return res;
    }
}