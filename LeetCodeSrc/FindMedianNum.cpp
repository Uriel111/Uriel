#include <vector>
using namespace std;
class Solution
{
public:
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        int i = 0;
        int j = 0;
        int newVecSize = nums1.size() + nums2.size();
        vector<int> newVec;
        newVec.resize(newVecSize);
        while (i + j != newVecSize)
        {
            if (i >= nums1.size())
            {
                newVec[i + j] = nums2[j];
                ++j;
                continue;
            }
            if (j >= nums2.size())
            {
                newVec[i + j] = nums1[i];
                ++i;
                continue;
            }

            if (nums1[i] <= nums2[j])
            {
                newVec[i + j] = nums1[i];
                ++i;
            }
            else
            {
                newVec[i + j] = nums2[j];
                ++j;
            }
            /* code */
        }
        if (newVecSize & 1)
        {
            return static_cast<double>(newVec[newVecSize >> 1]);
        }
        else
        {
            return (newVec[newVecSize >> 1] + newVec[(newVecSize >> 1) - 1]) / 2.0;
        }
    }
};