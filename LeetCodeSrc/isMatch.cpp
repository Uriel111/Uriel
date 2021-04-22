#include <string>
#include<limits>
using string = std::string;
class Solution
{
    bool isMatch(string s, string p)
    {
        int index = 0;
        while (index < s.size())
        {
            for (int pIndex = 0; pIndex != p.size(); ++pIndex)
            {
                if(s[index] == p[pIndex] || s[index] == '.')
                {
                    ++index;
                    continue;
                }hu

            }
        }
    }
};