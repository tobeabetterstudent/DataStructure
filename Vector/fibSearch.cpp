// @program: 02D3 实现Fibonacci查找
// @author: aslanwang
// @time: 2021-11-16

#include <iostream>
#include <vector>

using namespace std;

// MAX_SIZE是一个斐波那契数字 是fibNumber[11]
const int MAX_SIZE = 89;
const int SZ_INDEX = 11;

// fibNumber 计算一系列的斐波那契数 如：
// 0  1  2  3  4  5  6  7   8   9   10  11  12   13   14
// 0  1  1  2  3  5  8  13  21  34  55  89  144  233  377
vector<int>
fibNumber()
{
    vector<int> number;
    number.push_back(0);
    number.push_back(1);
    for (int i = 2; i < MAX_SIZE; i++)
    {
        number.push_back(number[i - 2] + number[i - 1]);
    }
    return number;
}

// findInitIndex 找到给定数字n在fibNumber中的索引 返回第一个大于等于n的fib数
// 这里直接使用斐波那契查找 因为fibNumber的size是固定的89 而89是fibNumber[11]
int findInitIndex(vector<int> &fibNumber, int target)
{
    int index = SZ_INDEX;
    int l = 0;
    int r = MAX_SIZE;
    while (l < r)
    {
        int mid = l + fibNumber[--index] - 1;
        if (target < fibNumber[mid])
        { // 转向mid左边去查 这里是fib[index-1] 在上面求mid时已经减过1 这里无需修改index
            r = mid;
        }
        else
        { // 转向mid右边去查 这里是fib[index-2] 在上面求mid时已经减过1 这里只需--index
            l = mid + 1;
            --index;
        }
    }
    return l;
}

// padding 将arr填充至size=sz
void padding(vector<int> &arr, int sz)
{
    while (arr.size() < sz)
    {
        arr.push_back(arr.back());
    }
}

// fibSearch 在[left,right)区间内查找target
int fibSearch(vector<int> &arr, int target)
{
    vector<int> fib = fibNumber();
    int index = findInitIndex(fib, arr.size());
    padding(arr, fib[index]);
    cout << "index = " << index << endl;
    int l = 0;
    int r = arr.size();
    while (l < r)
    {
        int mid = l + fib[--index] - 1;
        if (target < arr[mid])
        {
            r = mid;
        }
        else if (arr[mid] < target)
        {
            l = mid + 1;
            index--;
        }
        else
        {
            return mid;
        }
    }
    return -1;
}

void TestCase_1()
{
    vector<int> data = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61};
    cout << fibSearch(data, 43) << endl;
}

void TestCase_2()
{
    vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};
    cout << fibSearch(data, 14) << endl;
}

void TestCase_3()
{
    vector<int> data = {2, 3, 5, 7, 11, 13, 17};
    cout << fibSearch(data, 16) << endl;
}

int main()
{
    TestCase_1();
    TestCase_2();
    TestCase_3();
}

/*
Test Case:
1. V1={2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61} binarySearch(43)
2. V2={1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18} binarySearch(14)
3. V3={2, 3, 5, 7, 11, 13, 17} binarySearch(16)
*/