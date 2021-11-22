// @program: 02G3 实现bitMap
// @author: aslanwang
// @time: 2021-11-22

#ifndef BITMAP_H
#define BITMAP_H

class bitMap
{
private:
    int N;       // N表示bitMap所需要的字节数
    char *Bytes; // Bytes指向bitMap对应的那些字节

public:
    bitMap(int n);
    ~bitMap();
    void Add(int k);   // 向bitMap中加入k
    void Clear(int k); // 从bitMap中除去k
    bool Find(int k);  // 在bitMap中查找k
};

#endif