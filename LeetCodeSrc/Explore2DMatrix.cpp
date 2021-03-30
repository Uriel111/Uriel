#include <vector>
using ivector = std::vector<int>;
using i2DVector = std::vector<ivector>;
using bvector = std::vector<bool>;
using b2DVector = std::vector<bvector>;
class Solution
{
public:
    bool searchMatrix(i2DVector &matrix, int target)
    {
        b2dVector.resize(matrix.size());

        for (int i = 0; i != matrix.size(); ++i)
        {
            b2dVector[i].resize(matrix[i].size());

            for (int j = 0; j != matrix[i].size(); ++j)
            {
                b2dVector[i][j] = false;
            }
        }
        return SearchResult(matrix, 0, 0, target);
    }
    bool SearchResult(i2DVector &matrix, int i, int j, int target)
    {
        if (i >= matrix.size() || j >= matrix[i].size())
            return false;
        if (!b2dVector[i][j])
            b2dVector[i][j] = true;
        else
            return false;
        if (matrix[i][j] > target)
            return false;
        if (matrix[i][j] == target)
            return true;
        return SearchResult(matrix, i + 1, j, target) || SearchResult(matrix, i, j + 1, target);
    }

private:
    b2DVector b2dVector;
};