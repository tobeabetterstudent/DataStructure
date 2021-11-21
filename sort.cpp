// @program: 02E1 排序算法
// @author: aslanwang
// @time: 2021-11-14

#include <vector>
#include <iostream>

using namespace std;

// bubbleSort 对arr的[low,high)区间进行冒泡排序
// 考虑记录上一趟进行交换操作的最后位置last 这位置表明其之后的数组都实现了有序
// 在接下来的趟中 我们只需要将右边界直接调整到last即可
void bubbleSort(vector<int> &arr, int low, int high)
{
    while (low < high)
    {
        // last 上一趟进行交换操作的最后位置 初始值为low
        int last = low;
        for (int j = low + 1; j < high; j++)
        {
            if (arr[j - 1] > arr[j])
            {
                last = j;
                swap(arr[j - 1], arr[j]);
            }
        }
        high = last;
    }
}

void TestBubbleSort_1()
{
    vector<int> data = {6, 7, 3, 2, 1, 5, 8, 7, 4};
    bubbleSort(data, 0, data.size());
    for (auto &&v : data)
    {
        cout << v << '\t';
    }
    cout << endl;
}

int main()
{
    TestBubbleSort_1();
}