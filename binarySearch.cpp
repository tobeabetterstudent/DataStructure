// @program: 02D2 实现普通的二分查找 并统计查找长度
// @author: aslanwang
// @time: 2021-11-16

#include <iostream>
#include <vector>

using namespace std;

// binarySearch 在[left,right)区间内查找target 并将查找长度存储到cnt
int binarySearch(vector<int> &arr, int left, int right, int target, int &cnt)
{
    cnt = 0;
    while (left < right)
    {
        int mid = (left + right) >> 1;
        if (target < arr[mid])
        {
            right = mid;
            cnt++;
        }
        else if (arr[mid] < target)
        {
            left = mid + 1;
            cnt += 2;
        }
        else
        {
            cnt += 2;
            return mid;
        }
    }
}

void TestCase_1()
{
    vector<int> data = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61};
    int cnt = 0;
    binarySearch(data, 43, 0, data.size(), cnt);
    cout << cnt << endl;
}

void TestCase_2()
{
    vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};
    int cnt = 0;
    binarySearch(data, 14, 0, data.size(), cnt);
    cout << cnt << endl;
}

void TestCase_3()
{
    vector<int> data = {2, 3, 5, 7, 11, 13, 17};
    int cnt = 0;
    binarySearch(data, 16, 0, data.size(), cnt);
    cout << cnt << endl;
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