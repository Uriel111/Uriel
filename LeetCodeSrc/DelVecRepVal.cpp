#include <vector>
#include <iostream>
using namespace std;
class Solution
{
public:
    int removeDuplicates(vector<int> &nums)
    {
        auto it = nums.begin();
        while (it < nums.end())
        {
            if (it + 1 < nums.end() && *it == *(it + 1))
            {
                int val = *it;
                it = it + 2;

                while (it < nums.end())
                {
                    if (*it == val)
                    {
                        nums.erase(it);
                    }
                    else
                        break;
                }
            }
            else
                ++it;
        }
        return nums.size();
    }
};
int main()
{
    vector<int> nums{
        10,
        10,
        10,
        10,
        10,
        10,
        0,
        0,
        0,
        0,
    };
    static Solution slu;
    slu.removeDuplicates(nums);
    for (auto num : nums)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}