#include <vector>
#include <limits>
#include <queue>
using pQueue = std::queue<std::pair<int, int>>;
using iVector = std::vector<int>;
using iVector2D = std::vector<iVector>;
using bVector = std::vector<bool>;
using bVector2D = std::vector<bVector>;
class Solution
{
public:
    iVector2D updateMatrix(iVector2D &matrix)
    {

        iVector2D resMatrix = matrix;
        mMaxtrixFlag.resize(matrix.size());
        pQueue pQue;
        for (int i = 0; i != matrix.size(); ++i)
        {
            mMaxtrixFlag[i].resize(matrix[i].size());
            for (int j = 0; j != matrix[i].size(); ++j)
            {
                mMaxtrixFlag[i][j] = false;
            }
        }

        for (int i = 0; i != matrix.size(); ++i)
        {
            for (int j = 0; j != matrix[i].size(); ++j)
            {
                if (matrix[i][j] == 0)
                {
                    pQue.push(std::make_pair(i, j));
                }
            }
        }
        int distance = 0;
        auto SetMatrix = [this, &pQue, &resMatrix](int i, int j, int distance) {
            if (i < 0 || j < 0 || i >= resMatrix.size() || j >= resMatrix[i].size())
                return;
            if (!(this->mMaxtrixFlag[i][j]))
                this->mMaxtrixFlag[i][j] = true;
            else
                return;
            resMatrix[i][j] = distance;
            pQue.push(std::pair(i + 1, j));
            pQue.push(std::pair(i, j + 1));
            pQue.push(std::pair(i - 1, j));
            pQue.push(std::pair(i, j - 1));
        };
        while (!pQue.empty())
        {

            int size = pQue.size();
            for (int i = 0; i != size; ++i)
            {
                auto coordinate = pQue.front();
                pQue.pop();
                SetMatrix(coordinate.first, coordinate.second, distance);
            }
            distance += 1;
        }

        return resMatrix;
    }

public:
    void SetMatrix(iVector2D &matrix, int i, int j, int distance)
    {
    }
    bVector2D mMaxtrixFlag;
};