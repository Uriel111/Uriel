#include <vector>
#include <string>
using namespace std;
class Solution
{
public:
    string convert(string s, int numRows)
    {
        vector<string> sVec;
        if (numRows == 1)
            return s;
        sVec.resize(numRows);
        int curIndex = 0;
        int totalIndex = 0;
        int step = 1;
        int i = 0;
        while (i < s.size())
        {

            if (curIndex == 0)
            {
                int end = i + numRows >= s.size() ? s.size() : i + numRows;
                for (int j = i; j != end; ++j)
                {
                    sVec[j - i] += s[j];
                }
                i = end;
                curIndex = numRows - 1;
            }
            else
            {
                sVec[curIndex] += s[i];
                ++i;
            }
            curIndex -= 1;
        }
        string ans;
        for (int i = 0; i != sVec.size(); ++i)
        {
            ans += sVec[i];
        }
        return ans;
    }
};