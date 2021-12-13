// @question: 给定一颗真二叉树的 前序 + 后序遍历序列建树 保证节点编号两两不同 最终输出中序遍历序列
// @author: aslanwang
// @time: 2021-12-7
// @solve: 在这样的情况下 只要当前建树区间不为空 则当前子树根必有两个孩子
//    前序序列形如 R LC...... RC........
//    后序序列形如 ........LC........RC R
// 据此可以确定R的左右子树

#include <cstdio>

int n; // n表示节点个数
const int MAXSZ = 4000001;
int pre[MAXSZ] = {0};  // 前序序列
int post[MAXSZ] = {0}; // 后序序列

struct Node
{
    int val;
    Node *left;
    Node *right;
    Node(int _val) : val(_val), left(nullptr), right(nullptr)
    {
        return;
    }
};

// create 在pre[l1~h1] 和 post[l2~h2]之内建树
Node *create(int l1, int h1, int l2, int h2)
{
    if (h1 < l1 || l1 >= n)
    {
        return nullptr;
    }
    Node *root = new Node(pre[l1]);
    if (h1 == l1)
    {
        return root;
    }
    // 确定左子树的元素个数
    int i = l2;
    for (; i < h2; i++)
    {
        if (post[i] == pre[l1 + 1])
        {
            break;
        }
    }
    // 这里左子树包括post[i]
    int numLeft = i - l2 + 1;
    root->left = create(l1 + 1, l1 + numLeft, l2, i);
    root->right = create(l1 + numLeft + 1, h1, i + 1, h2 - 1);
    return root;
}

void inTraverse(Node *root)
{
    if (!root)
    {
        return;
    }
    inTraverse(root->left);
    printf("%d ", root->val);
    inTraverse(root->right);
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &pre[i]);
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &post[i]);
    }
    Node *root = create(0, n - 1, 0, n - 1);
    inTraverse(root);
}