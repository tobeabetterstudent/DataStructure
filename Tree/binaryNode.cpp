// @program: 05E1-4 实现binaryNode
// @author: aslanwang
// @time: 2021-12-2

#include "binaryNode.h"
#include <stack>

/**
 * @brief
 *
 * @tparam T
 * @tparam VST
 * @param root
 * @param visit
 */
template <typename T>
template <typename VST>
void binaryNode<T>::preTraverse(binaryNode<T> *root, VST &visit)
{
    if (!root)
    {
        return;
    }
    visit(root->data);
    preTraverse(root->left, visit);
    preTraverse(root->right, visit);
}