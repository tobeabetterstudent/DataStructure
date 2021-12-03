// @program: 实现对树的中序遍历
// @author: aslanwang
// @time: 2021-12-3
#include <iostream>
#include <stack>

using namespace std;

struct Node
{
    int val;
    Node *left;
    Node *right;
};

class VST
{
public:
    void operator()(int v)
    {
        cout << v << endl;
    }
} visit;

// in_Traverse_1 递归方式进行中序遍历
void in_Traverse_1(Node *root)
{
    if (!root)
    {
        return;
    }
    in_Traverse_1(root->left);
    visit(root->val);
    in_Traverse_1(root->right);
}

// in_Traverse_2 迭代方式进行中序遍历
// 首先对root子树一路向左将沿途所有节点入栈  直到最左边的叶子 访问该节点 再以该节点的右子树为根重复中序遍历
void in_Traverse_2(Node *root)
{
    stack<Node *> st;
    while (1)
    {
        while (root)
        {
            st.push(root);
            root = root->left;
        }
        if (st.empty())
        {
            return;
        }
        root = st.top();
        st.pop();
        visit(root->val);
        root = root->right;
    }
}