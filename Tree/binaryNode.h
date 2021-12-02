#ifndef _BINARY_NODE_
#define _BINARY_NODE_

template <typename T>
struct binaryNode
{
    binaryNode<T> *parent;
    binaryNode<T> *left, right;
    T data;

    template <typename VST>
    void preTraverse(binaryNode<T> *root, VST &visit); // 先序遍历函数 传入函数参数visit
};

#endif