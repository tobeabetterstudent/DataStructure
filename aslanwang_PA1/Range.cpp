// @question: 给定数轴上n个点的位置，对于任一闭区间 [a, b]，试计算落在其内的点数。
// @author: aslanwang
// @time: 2021-11-24
// @solve: 首先对点的位置做快排 其次对a,b在点上做二分查找 查找最后一个不大于b的和a-1的位置(即最后一个小于a的位置)

#include <iostream>

using namespace std;

const int MAXSZ = 1e6;
int n, m;          // 点的总数 和 查询次数
int points[MAXSZ]; // 数轴上的点

// randomParation 随机划分
int randomParation(int left, int right)
{
    int index = rand() % (right - left + 1) + left;
    swap(points[left], points[index]);
    int temp = points[left];
    while (left < right)
    {
        while (left < right && temp <= points[right])
        {
            right--;
        }
        points[left] = points[right];
        while (left < right && points[left] <= temp)
        {
            left++;
        }
        points[right] = points[left];
    }
    points[left] = temp;
    return left;
}

// quickSort 对points数组[begin,end]排序
void quickSort(int left, int right)
{
    if (left < right)
    {
        int split = randomParation(left, right);
        quickSort(left, split - 1);
        quickSort(split + 1, right);
    }
}

// binarySearchLE 在[l,r)区间中找到points中最后一个不大于target的下标
int binarySearchGE(int target)
{
    int l = 0, r = n;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (target < points[mid])
        { // 如果target < points[mid] 则需要去mid左边查找
            r = mid;
        }
        else
        { // points[mid] <= target 则继续去mid右边查找 因此while出口时l指向第一个大于target的元素
            l = mid + 1;
        }
    }
    return l - 1;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &points[i]);
    }
    quickSort(0, n - 1);
    int l, r;
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d", &l, &r);
        // 实际上查找最后一个小于等于r的位置 和最后一个小于l的位置
        printf("%d\n", binarySearchGE(r) - binarySearchGE(l - 1));
    }
}