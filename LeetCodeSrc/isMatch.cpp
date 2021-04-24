#include <string>
#include <limits>
#include <vector>

using bVector = std::vector<bool>;
using b2DVector = std::vector<bVector>;
using string = std::string;
class Solution
{
public:
    bool isMatch(string s, string p)
    {
        int sSize = s.size();
        int pSize = p.size();
        b2DVector bMatrix;
        auto match = [&](int i, int j) {
            if (i == 0)
                return false;
            if (p[j - 1] == '.')
                return true;
            return s[i - 1] == p[j - 1];
        };
        bMatrix.resize(sSize + 1);
        for (int i = 0; i != bMatrix.size(); ++i)
            bMatrix[i].resize(pSize + 1);
        bMatrix[0][0] = true;
        for (int i = 0; i != bMatrix.size(); ++i)
        {
            for (int j = 1; j != bMatrix[i].size(); ++j)
            {
                if (p[j - 1] != '*')
                {
                    if (match(i, j))
                    {
                        bMatrix[i][j] = bMatrix[i - 1][j - 1];
                    }
                    else
                        bMatrix[i][j] = false;
                }
                else
                {
                    if (match(i, j - 1))
                    {
                        bMatrix[i][j] = bMatrix[i - 1][j] || bMatrix[i][j - 2];
                    }
                    else
                    {
                        bMatrix[i][j] = bMatrix[i][j - 2];
                    }
                }
            }
        }
        return bMatrix[s.size()][p.size()];
    }
};