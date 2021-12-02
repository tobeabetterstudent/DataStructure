#include "list.h"

/**
 * @brief 内部调用函数
 * 
 */
template <typename T>
void List<T>::init()
{
    header = new ListNode<T>;  // 创建头哨兵 约定为头结点
    trailer = new ListNode<T>; // 创建尾哨兵 约定为尾结点
    header->pred = nullptr;
    header->succ = trailer;
    tailer->pred = header;
    tailer->succ = nullptr;
    _size = 0;
}

template <typename T>
void List<T>::clear()
{
    while (_size > 0)
    { // 当列表init后 只有header与trailer 这时_size=0 因此只需在_size>0时反复删除首结点即可
        ListNode<T> *p = header->succ;
        p->succ->pred = p->pred; // p的后继指向p的前驱
        p->pred->succ = p->succ; // p的前驱指向p的后继
        _size--;
        delete p;
    }
}

/**
 * @brief Construct a new List object
 * 
 */
template <typename T>
List<T>::List()
{
    init();
}

/**
 * @brief Write Function
 * 
 */
