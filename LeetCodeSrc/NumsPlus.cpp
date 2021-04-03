#include <vector>
#include <algorithm>
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution
{
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        int m = 0;
        int n = 0;
        ListNode *curNode;
        curNode = l1;
        while (curNode)
        {
            ++m;
            curNode = curNode->next;
        }
        curNode = l2;
        while (curNode)
        {
            ++n;
            curNode = curNode->next;
        }
        std::vector<int> resVec(std::max(m, n));

        m = 0;
        n = 0;
        curNode = l1;
        while (curNode)
        {
            resVec[m] += curNode->val;
            ++m;
            curNode = curNode->next;
        }
        curNode = l2;
        while (curNode)
        {
            resVec[n] += curNode->val;
            ++n;
            curNode = curNode->next;
            /* code */
        }
        for (int i = 0; i != resVec.size() - 1; ++i)
        {
            resVec[i + 1] += resVec[i] / 10;
            resVec[i] %= 10;
        }
        if (resVec[resVec.size() - 1] / 10)
        {
            int n = resVec[resVec.size() - 1] / 10;
            resVec[resVec.size() - 1] %= 10;

            resVec.push_back(n);
        }
        ListNode *res = new ListNode(0);
        curNode = res;
        for (int i = 0; i != resVec.size(); ++i)
        {
            curNode->next = new ListNode(resVec[i]);
            curNode = curNode->next;
        }
        return res->next;
    }
};