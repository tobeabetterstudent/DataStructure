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

// merge 将A的两个有序区间[low,mid)和[mid,high)合并到数组B
void merge(vector<int> &A, vector<int> &B, int low, int mid, int high)
{
    int i = low, j = mid;
    int k = low;
    while (i < mid && j < high)
    {
        B[k++] = A[i] < A[j] ? A[i++] : A[j++];
    }
    while (i < mid)
    {
        B[k++] = A[i++];
    }
    while (j < high)
    {
        B[k++] = A[j++];
    }
}

// mergeSort 对arr1的[low,high)区间进行归并排序
// 其中arr2是大小与arr1一致的额外空间
void mergeSort(vector<int> &arr1, vector<int> &arr2, int low, int high)
{
    if (high - low < 2)
    { // [low, high)只剩一个元素 这个子区间已经有序 可以直接返回
        return;
    }
    // 将[low,high)分为两个子区间 分别mergeSort
    int mid = (low + high) >> 1;
    mergeSort(arr1, arr2, low, mid);
    mergeSort(arr1, arr2, mid, high);
    merge(arr1, arr2, low, mid, high);
    // 将arr2中的数据复制回arr1
    for (int i = low; i < high; i++)
    {
        arr1[i] = arr2[i];
    }
}

void TestBubbleSort()
{
    vector<int> data = {6, 7, 3, 2, 1, 5, 8, 7, 4};
    bubbleSort(data, 0, data.size());
    for (auto &&v : data)
    {
        cout << v << '\t';
    }
    cout << endl;
}

void TestMergeSort()
{
    vector<int> arr1 = {6, 7, -1, 45, 23, -9, 3, 2, 1, 5, 8, 7, 4};
    vector<int> arr2(arr1.size());
    mergeSort(arr1, arr2, 0, arr1.size());
    for (auto &&v : arr1)
    {
        cout << v << '\t';
    }
    cout << endl;
}

int main()
{
    TestBubbleSort();
    TestMergeSort();
}