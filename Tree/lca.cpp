// @program: 实现查找树中两个节点的最近公共祖先
// @author: aslanwang
// @time: 2021-12-5

#include "binaryNode.h"

#define Node binaryNode<int>

Node *lowestCommonAncestor_1(Node *root, Node *p, Node *q)
{
    if (root == nullptr || root == p || root == q)
    {
        return root;
    }
    Node *l = lowestCommonAncestor_1(root->left, p, q);
    Node *r = lowestCommonAncestor_1(root->right, p, q);
    if (!l)
    {
        return r;
    }
    if (!r)
    {
        return l;
    }
    return root;
}