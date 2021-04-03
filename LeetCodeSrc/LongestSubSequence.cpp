#include <iostream>
#include <vector>
#include <string>
using namespace std;
using ivector = std::vector<int>;
using i2DVector = vector<ivector>;
class Solution
{
public:
    int longestCommonSubsequence(string text1, string text2)
    {
        string ans;
        i2DVector matrix;
        matrix.resize(text1.size() + 1);
        if (!text1.size() || !text2.size())
            return 0;
        int m = text1.size();
        int n = text2.size();
        matrix.resize(text1.size() + 1);
        for (int i = 0; i != matrix.size(); ++i)
            matrix[i].resize(text2.size() + 1);
        for (int i = 0; i != m + 1; ++i)
            matrix[i][0] = 0;
        for (int j = 0; j != n + 1; ++j)
            matrix[0][j] = 0;
        for (int i = 1; i != m + 1; ++i)
        {
            for (int j = 1; j != n + 1; ++j)
            {
                if (text1[i - 1] == text2[j - 1])
                {
                    matrix[i][j] = matrix[i - 1][j - 1] + 1;
                }
                else
                {
                    matrix[i][j] = max(matrix[i - 1][j], matrix[i][j - 1]);
                }
            }
        }

        return matrix[m][n];
    }
};