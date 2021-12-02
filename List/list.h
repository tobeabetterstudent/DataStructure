#ifndef _LIST_H_
#define _LIST_H_

#include "listNode.h"

// list容器
// 列表节点模板类 以双向链表形式实现
template <typename T>
class List
{
private:
    /**
     * @brief 内部成员
     * 
     */
    int _size;            // list的规模
    ListNode<T> *header;  // 头部哨兵
    ListNode<T> *trailer; // 尾部哨兵

protected:
    /**
     * @brief 内部调用函数
     * 
     */
    void init();                          // 列表创建时初始化
    void clear();                         // 清除所有节点
    void copyNodes(ListNode<T> *, int n); // 复制列表从给定位置其的n项

public:
    /**
     * @brief Construct a new List object
     * 
     */
    List();                               // 默认构造
    List(const List<T> &L);               // 整体复制列表L
    List(const List<T> &L, int r, int n); // 整体复制列表L从第r项起的n项
    List(ListNode<T> *p, int n);          // 复制列表中子位置p起的n项

    /**
     * @brief Destroy the List object
     * 
     */
    ~List(); // 释放列表所有节点

    /**
     * @brief Read Only Function
     *
     */
    int size() const;           // 返回列表规模
    bool empty() const;         // 判空
    ListNode<T> *first() const; // 返回首节点
    ListNode<T> *last() const;  // 返回末节点
    bool valid(ListNode<T> *p); // 判断位置p对胃是否合法

    /**
     * @brief Write Function
     * 
     */
    ListNode<T> *insertAsFirst(const T &e);          // 将e当做首节点插入
    ListNode<T> *insertAsLast(const T &e);           // 将e当做末节点插入
    ListNode<T> *insert(ListNode<T> *p, const T &e); // 将e作为p的后继节点插入列表
    ListNode<T> *insert(const T &e, ListNode<T> *p); // 将e作为p的前驱节点插入列表
    T remove(ListNode<T> *p);                        // 删除合法位置p处的节点 返回被删除的节点值
};

#endif