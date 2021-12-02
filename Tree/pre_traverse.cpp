// @program: 实现对树的前序遍历
// @author: aslanwang
// @time: 2021-12-2
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

// Traverse_1 递归方式进行前序遍历
void Traverse_1(Node *root)
{
    if (!root)
    {
        return;
    }
    visit(root->val);
    Traverse_1(root->left);
    Traverse_1(root->right);
}

// Traverse_2 接住栈实现迭代式前序访问
void Traverse_2(Node *root)
{
    stack<Node *> st;
    if (root)
    {
        st.push(root);
    }
    while (!st.empty())
    {
        Node *parent = st.top();
        visit(parent->val);
        st.pop();
        // 这里注意到stack是先进后出的顺序 所以在pre遍历下 先入右子树
        if (parent->right)
        {
            st.push(parent->right);
        }
        if (parent->left)
        {
            st.push(parent->left);
        }
    }
}