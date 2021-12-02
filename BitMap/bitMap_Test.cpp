#include "bitMap"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void TestBitMap_1()
{
    vector<int> arr = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10, 11, 12, 13, 14, 15, 16, 63, 45, 21, 38};
    int n = 0;
    for (auto &&v : arr)
    {
        n = max(n, v);
    }
    bitMap mp(n);
    for (auto &&v : arr)
    {
        mp.Add(v);
    }
    for (auto &&v : arr)
    {
        if (!mp.Find(v))
        {
            cout << "Error!" << endl;
            return;
        }
    }
    cout << "Succeed!" << endl;
}

int main()
{
    TestBitMap_1();
}