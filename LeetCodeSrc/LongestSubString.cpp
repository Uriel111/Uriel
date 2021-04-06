#include <string>
#include <set>
using cSet = std::set<char>;
using string = std::string;
class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        cSet mStrSet;
        int maxLength = 0;
        int begin = 0;
        int end = 0;
        while (end < s.size())
        {
            if (mStrSet.find(s[end]) == mStrSet.end())
            {
                mStrSet.insert(s[end]);
            }
            else // contain repeat sub str
            {
                while (mStrSet.find(s[end]) != mStrSet.end())
                {
                    mStrSet.erase(mStrSet.find(s[begin]));
                    ++begin;
                }
                mStrSet.insert(s[end]);
            }

            ++end;
            maxLength = std::max(maxLength, static_cast<int>(mStrSet.size()));

            /* code */
        }
    }
};