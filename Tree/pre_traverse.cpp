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
// 注意到这实际上是一个尾递归 在回归过程中不需要任何操作
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

// Traverse_2 通过栈实现迭代式前序访问
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

// Traverse_2 通过更一般的形式去实现迭代式前序访问
// 注意到对每个子树的前序遍历都是先一路访问所有的左节点 再从最下面返回去——前序遍历——它们的右子树
void Traverse_3(Node *root)
{
    stack<Node *> st;
    while (1)
    { // 对root子树 一路访问其所有的左孩子 并将右孩子压入栈
        while (root)
        {
            visit(root->val);
            if (root->right)
            {
                st.push(root->right);
            }
            root = root->left;
        }
        // 再从树底端返回去前序遍历右子树 对栈中的弹出的右子树又进入下一次循环
        if (st.empty())
        {
            return;
        }
        root = st.top();
        st.pop();
    }
}