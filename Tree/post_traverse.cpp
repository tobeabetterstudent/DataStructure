// @program: 实现对树的后序遍历
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

// post_Traverse_1 递归方式进行后序遍历
void post_Traverse_1(Node *root)
{
    if (!root)
    {
        return;
    }
    post_Traverse_1(root->left);
    post_Traverse_1(root->right);
    visit(root->val);
}

// post_Traverse_2 迭代方式进行后序遍历
// 对以root为根的子树 沿其左子树一路向下将沿途所有节点都入栈 直到最左边的一个节点A没有左子树 这时要去访问其右子树
// 因此继续对其右子树进行后序遍历 当右子树遍历完成后 该节点A又一次出现在栈顶 这时访问它 注意到后序遍历中 A的右孩子一定紧紧在A之前
// 因此需要设置一个变量pre记录每个节点之前被访问的那个节点
// 如果这个节点恰好是当前栈顶的右子树 则可以访问栈顶并更新pre
// 如果不是 则需要继续对右子树进行后序遍历
void post_Traverse_2(Node *root)
{
    if (!root)
    {
        return;
    }
    stack<Node *> st;
    Node *mark = nullptr;
    while (1)
    {
        // 对root子树进行后序遍历
        while (root)
        {
            st.push(root);
            root = root->left;
        }
        if (st.empty())
        {
            return;
        }
        // 这时root已经为nullptr了 在访问栈顶节点前还要确保访问其右子树 右孩子的前驱应该为nullptr
        mark = nullptr;
        while (!st.empty())
        {
            root = st.top();
            // 对当前栈顶 经过第一个while循环 可以确保访问了其左子树 那么是否访问过其右子树呢？
            if (root->right == mark)
            { // root右子树已经访问过 可以访问root 并更新pre 以便于接下来这个root又是上面节点的右子树
                st.pop();
                visit(root->val);
                mark = root;
            }
            else
            {
                root = root->right;
                break;
            }
        }
    }
}
