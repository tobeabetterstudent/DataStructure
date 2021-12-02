// @program: 02D2 实现普通的二分查找 并统计查找长度
// @author: aslanwang
// @time: 2021-11-16; 2021-11-19 按照新的语义重写二分查找

#include <iostream>
#include <vector>

using namespace std;

// updateBinarySearch 新语义下的二分查找
// 在[left,right)区间中查找target
// 返回arr中不大于target的最后一个id 这样我们可以直接将target插入到id 而保持arr仍然有序
// 也即是找到第一个大于target的元素index 返回index-1
int updateBinarySearch(vector<int> &arr, int target, int left, int right)
{
    while (left < right)
    {
        int mid = (left + right) >> 1;
        if (target < arr[mid])
        { // 直接去mid的左边查找
            right = mid;
        }
        else
        { // arr[mid] <= target 去mid右边查找
            left = mid + 1;
        }
    }
    // 出口时 left指向第一个大于target的元素
    return left - 1;
}

// binarySearch 在[left,right)区间内查找target 并将查找长度存储到cnt
int binarySearch(vector<int> &arr, int target, int left, int right, int &cnt)
{
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
    cout << binarySearch(data, 43, 0, data.size(), cnt) << '\t' << cnt << endl;
    cout << updateBinarySearch(data, 43, 0, data.size()) << endl;
}

void TestCase_2()
{
    vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};
    int cnt = 0;
    cout << binarySearch(data, 14, 0, data.size(), cnt) << '\t' << cnt << endl;
    cout << updateBinarySearch(data, 14, 0, data.size()) << endl;
}

void TestCase_3()
{
    vector<int> data = {2, 3, 5, 7, 11, 13, 17};
    int cnt = 0;
    cout << binarySearch(data, 16, 0, data.size(), cnt) << '\t' << cnt << endl;
    cout << updateBinarySearch(data, 16, 0, data.size()) << endl;
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