#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
using namespace std;
/*
  i < j < k 满足 nums[i] < nums[k] < nums[j]
*/
class Solution
{
public:
    bool find132pattern(vector<int> &nums)
    {
        multiset<int> mSet;
        int k = nums.size();
        if (k < 3)
            return false;
        for (int l = 2; l != nums.size(); ++l)
        {
            mSet.insert(nums[l]);
        }
        int i = nums[0];
        for (int l = 1; l != nums.size() - 1; ++l)
        {
            if (i < nums[l])
            {
                if (mSet.upper_bound(i) != mSet.end() && *mSet.upper_bound(i) < nums[l])
                    return true;
            }
            i = min(i, nums[l]);
            mSet.erase(mSet.find(nums[l + 1]));
        }
        return false;
    }
};
int main()
{
    return 0;
}