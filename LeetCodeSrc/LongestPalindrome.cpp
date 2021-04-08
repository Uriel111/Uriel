#include <string>
#include <vector>
using namespace std;
using BVecMatrix = vector<vector<bool>>;
class Solution
{
public:
    string longestPalindrome(string s)
    {
        int strSize = s.size();
        BVecMatrix bVecMatrix;
        bVecMatrix.resize(strSize);
        string ans;
        for (int i = 0; i != bVecMatrix.size(); ++i)
        {
            bVecMatrix[i].resize(strSize);
            for (int j = i; j != bVecMatrix[i].size(); ++j)
            {
                if (i == j)
                {
                    bVecMatrix[i][j] = true;
                    if (ans.size() == 0)
                    {
                        ans = s[i];
                    }
                }
                else if (j - i == 1)
                {
                    bVecMatrix[i][j] = s[i] == s[j];
                    if (s[i] == s[j])
                        ans = string(s.begin() + i, s.begin() + j + 1);
                }
                else
                    break;
            }
        }

        for (int i = bVecMatrix.size() - 1; i >= 0; --i)
        {
            for (int j = i + 2; j < bVecMatrix[i].size(); ++j)
            {
                bVecMatrix[i][j] = bVecMatrix[i + 1][j - 1] && s[i] == s[j];
                if (bVecMatrix[i][j] && j - i + 1 > ans.size())
                {
                    ans = string(s.begin() + i, s.begin() + j + 1);
                }
            }
        }
        return ans;
    }
};