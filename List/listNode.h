#ifndef _LISTNODE_H_
#define _LISTNODE_H_

// 列表节点模板类 以双向链表形式实现
template <typename T>
class ListNode
{
private:
    T value;        // 节点值
    ListNode *pred; // 前驱
    ListNode *succ; // 后继`
public:
    ListNode();
    ListNode(T e, ListNode *p = nullptr, ListNode *s = nullptr);
    ListNode<T> *insertAsPred(const T &e); // 在this前插入节点 其值为e 并返回该节点
    ListNode<T> *insertAsSucc(const T &e); // 在this后插入节点 其值为e 并返回该节点
};

#endif