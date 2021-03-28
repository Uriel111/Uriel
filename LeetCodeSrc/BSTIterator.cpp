#include <stack>

class TreeNode
{
public:
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class BSTIterator
{
public:
    BSTIterator(TreeNode *root)
    {
        StoreTreeNode(root);
    }
    ~BSTIterator()
    {
    }
    void StoreTreeNode(TreeNode *root)
    {
        while (root)
        {
            _mTreeNodeStack.push(root);
            root = root->left;
        }
        curNode = root;
    }
    int next()
    {
        int value = 0;
        if (curNode)
        {
            value = curNode->val;
            curNode = curNode->left;
        }
        auto curMidTreeNode = _mTreeNodeStack.top();
        _mTreeNodeStack.pop();
        value = curMidTreeNode->val;
        StoreTreeNode(curMidTreeNode->right);
        return value;
    }
    bool hasNext()
    {
        if (curNode)
            return true;
        return !_mTreeNodeStack.empty();
    }

private:
    std::stack<TreeNode *> _mTreeNodeStack;
    TreeNode *curNode;
    TreeNode *head;
};