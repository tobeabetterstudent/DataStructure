#include "bitMap.h"

bitMap::bitMap(int n = 8)
{
    N = (n + 7) >> 3;
    Bytes = new char[N];
}

bitMap::~bitMap()
{
    if (Bytes != nullptr)
    {
        delete (Bytes);
        Bytes = nullptr;
    }
}

// Add 向bitMap中加入k
void bitMap::Add(int k)
{
    if ((k >> 3) >= N)
    { // 越界
        return;
    }
    Bytes[k >> 3] |= (1 << (k & 0x07));
}

// Clear 从bitMap中除去k
void bitMap::Clear(int k)
{
    if ((k >> 3) >= N)
    { // 越界
        return;
    }
    Bytes[k >> 3] &= ~(1 << (k & 0x07));
}

// Find 在bitMap中查找k
bool bitMap::Find(int k)
{
    if ((k >> 3) >= N)
    { // 越界
        return false;
    }
    return Bytes[k >> 3] & (1 << (k & 0x07));
}