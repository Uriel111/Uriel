class ListNode
{
public:
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *listNode) : val(x), next(listNode) {}
};
class Solution
{
public:
    ListNode *rotateRight(ListNode *head, int k)
    {
        int listNodeSize = 0;
        ListNode *curListNode = head;

        while (curListNode != nullptr)
        {
            listNodeSize += 1;
            curListNode = curListNode->next;
        }
        curListNode = head;
        if (listNodeSize <= 0)
            return head;
        ListNode *preLeftHead = head;

        k %= listNodeSize;
        for (int i = 0; i != listNodeSize - k; ++i)
        {
            if (i == listNodeSize - k - 1)
            {
                ListNode *tempListNode = curListNode->next;
                curListNode->next = nullptr;
                curListNode = tempListNode;
                continue;
            }
            curListNode = curListNode->next;
        }
        ListNode *preRightHead = curListNode;
        if (preRightHead == nullptr)
            return preLeftHead;
        curListNode = preRightHead;
        while (curListNode && curListNode->next)
        {
            curListNode = curListNode->next;
        }
        if (curListNode)
            curListNode->next = preLeftHead;
        return preRightHead;
    }
};
