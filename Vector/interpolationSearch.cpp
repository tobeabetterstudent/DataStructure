// @program: 02D6 实现插值查找 复杂度为log(logn) 要求数据在排序后 满足均匀随机的独立分布 则在这种情况下可以将数据落在x-o-y上一条近似的直线
// @author: aslanwang
// @time: 2021-11-21
#include <iostream>
#include <vector>

using namespace std;

// interpolationSearch 实现在[begin, end)之间插值查找target
// 对target假设其下标为id 则满足 (arr[end] - arr[begin]) / (end - begin) = (target - arr[begin]) / (id - begin)
int interpolationSearch(vector<int> &arr, int target, int begin, int end)
{
    while (begin < end)
    {
        int mid = (target - arr[begin]) * (end - begin) / (arr[end] - arr[begin]) + begin;
        if (target < arr[mid])
        {
            end = mid;
        }
        else if (arr[mid] < target)
        {
            begin = mid + 1;
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
    cout << interpolationSearch(data, 43, 0, data.size()) << endl;
}

int main()
{
    TestCase_1();
}