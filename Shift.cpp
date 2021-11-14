// @program: 01XA1-2 循环向左移k位的三种实现方式
// @author: aslanwang
// @time: 2021-11-13

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// ShiftByViolence 每一轮次将所有的数字左移1位 一共移动k个轮次
void ShiftByViolence(vector<int> &arr, int k)
{
    int m = arr.size();
    for (int i = 1; i <= k; i++)
    {
        int temp = arr[0];
        for (int j = 0; j < m - 1; j++)
        {
            arr[j] = arr[j + 1];
        }
        arr[m - 1] = temp;
    }
}

// gcd 计算a b的最大公约数数
int gcd(int a, int b)
{
    if (!b)
    {
        return a;
    }
    return gcd(b, a % b); //a % b一定小于b
}

// ShiftByOneStep 首先设置temp保存arr[0] 由此空出了0的位置 设n = arr.size() 就可以把(0+k) %n 移到0 周而复始
// question: 若gcd(n,k)!= 1 则n = x*g ; k = y*g 于是当移动m次后就有当前位置为 m*k=m*y*g % n = 0 也就是又回到了0 形成了一个不覆盖所有元素的循环
// 因此还要继续以1,2...g-1为起始进行新的循环
void ShiftByOneStep(vector<int> &arr, int k)
{
    int m = arr.size();
    int g = gcd(m, k);
    int temp = arr[0];
    int x;
    for (int i = 0; i < g; i++)
    {
        x = i;
        while ((x + k) % m != i)
        { // 以循环到起点为终止
            arr[x] = arr[(x + k) % m];
            x = (x + k) % m;
        }
    }
    arr[x] = temp;
}

// ShiftByReverse 通过翻转数组实现左移 0 1 2 3 4 5 6 7 8 9
// 首先翻转前k个元素 再将剩下的那些元素做局部翻转 最后将整个数组翻转
void ShiftByReverse(vector<int> &arr, int k)
{
    reverse(arr.begin(), arr.begin() + k);
    reverse(arr.begin() + k, arr.end());
    reverse(arr.begin(), arr.end());
}

int main()
{
    vector<int> arr = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    // ShiftByViolence(arr, 3);
    // for (auto &&x : arr)
    // {
    //     cout << x << '\t';
    // }
    // ShiftByOneStep(arr, 3);
    // for (auto &&x : arr)
    // {
    //     cout << x << '\t';
    // }
    ShiftByReverse(arr, 3);
    for (auto &&x : arr)
    {
        cout << x << '\t';
    }
}
