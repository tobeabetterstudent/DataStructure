// @question: 祖玛游戏
// @author: aslanwang
// @time: 2021-11-25
// @solve: 对珠子建立双向链表 每次插入一个节点 都去查找是否形成了可消除串
// 插入一个节点向前查找到befor 向后查找到after 若满足条件则删除区间(before,after) 则这时如果有新的可消除串 则一定是before+i,...before,after,...after+j形式
// 则还需要从before开始向两边检查
// ps： 要处理输入起始字符串为空的情况 使用string::getline(std::cin, str)
#include <iostream>
#include <string>

using namespace std;

int n = 0, k = 0; // n从操作 每次将珠子插入到k
char newBeard;    // 新珠子的颜色
const int MAXSZ = 1e5;
string originalSequence;

struct ListNode
{
    char value;
    ListNode *pred;
    ListNode *succ;
    ListNode() : value('\0'), pred(nullptr), succ(nullptr)
    {
        return;
    }
    ListNode(char c) : value(c), pred(nullptr), succ(nullptr)
    {
        return;
    }
};

class List
{
private:
    ListNode *header;
    ListNode *trailer;
    int _size;

public:
    // List 默认构造
    List() : _size(0)
    {
        header = new ListNode();
        trailer = new ListNode();
        header->succ = trailer;
        trailer->pred = header;
    }
    // 析构函数
    ~List()
    {
        ListNode *p = header->succ;
        while (p != trailer)
        {
            delete p->pred;
            p = p->succ;
        }
        delete trailer;
    }
    // insertAfter 将val作为p的后继插入到List
    ListNode *insertAfter(ListNode *p, char &val)
    {
        ListNode *node = new ListNode(val);
        node->succ = p->succ;
        p->succ->pred = node;
        p->succ = node;
        node->pred = p;
        return node;
    }

    // insertInto 在位置index处插入val
    ListNode *insertInto(int index, char val)
    {
        ListNode *p = header;
        while (index--)
        {
            p = p->succ;
        }
        return insertAfter(p, val);
    }

    // removeBetween 删除给定(起点,终点)之间的那段序列
    void removeBetween(ListNode *begin, ListNode *end)
    {
        ListNode *p = begin->succ;
        ListNode *q = p->succ;
        while (p != end)
        {
            delete p;
            p = q;
            q = q->succ;
        }
        begin->succ = end;
        end->pred = begin;
    }

    // checkContinueSeries 给定起点 向两边检查连续的珠子数目
    void checkContinueSeries(ListNode *p)
    {
        if (p == header || p == trailer)
        {
            return;
        }

        int m = 0;
        ListNode *before = p->pred; // 向p前方去找与p颜色相同的数目
        while (before != header && before->value == p->value)
        { // 向前在befor有效时
            before = before->pred;
            m++;
        }
        int n = 0;
        ListNode *after = p->succ; // 向p后方去找与p颜色相同的数目
        while (after != trailer && after->value == p->value)
        {
            after = after->succ;
            n++;
        }
        if (m + n + 1 >= 3)
        { // +1是因为m n 中都没有计算节点p
            removeBetween(before, after);
            checkContinueSeries(before);
        }
    }

    // traverse 遍历List
    void traverse()
    {
        ListNode *p = header->succ;
        if (p == trailer)
        {
            putchar('-');
            return;
        }
        while (p != trailer)
        {
            putchar(p->value);
            p = p->succ;
        }
    }
};

int main()
{
    getline(cin, originalSequence);
    List myList;
    for (int i = 0; i < originalSequence.length(); i++)
    {
        myList.insertInto(i, originalSequence[i]);
    }

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        scanf("%d %c", &k, &newBeard);
        ListNode *p = myList.insertInto(k, newBeard);
        myList.checkContinueSeries(p);
        myList.traverse();
        putchar('\n');
    }
}