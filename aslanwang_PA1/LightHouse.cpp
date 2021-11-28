// @question: 给定二维平面上n个点的位置，假定每个点都照亮其东北、西南两个对顶的直角区域 问能照亮彼此的灯塔对数
// @author: aslanwang
// @time: 2021-11-24
// @solve: 实际上考察两个点的相对位置 (x1,y1)与(x2,y2) 注意到所有点的横纵坐标都不同 因此只有在(x1<x2)&&(y1<y2) || (x2<x1)&&(y2<y1)时这一对点符合题意
// 因此可以化二维为一维，也就是对lightHouse根据x坐标排序，在x升序的条件下来考虑前后两个等他的y坐标相对关系
// 在排序后，实际上对i < j 只需要lights[i]_y < lights[j]_y 则形成了一对可相互照亮的灯塔 也即是求y的顺序对数
// 采用分治法: 将点分成两半 求每一半内的ret 再求两半合并起来的ret --> 形同归并排序
// 在这种分治策略下 递归基以1个点为边界 而因此实际的求解工作都是在将两个区间合并计算时做的 而这样设计恰好使得前后两个区间合并时 前者的横坐标小于后者
// 考察左右两个区间分别为[a1,a2,a3] [b1,b2,b3] 考虑merge时出现的情况，对每一次比较，在输入限制横纵坐标都不重复的情况下,无非以下2种可能：
//      ai_y < bj_y 则得知ai与右区间的所有剩余元素都形成顺序对 因此有High(2) - j个 左半边内部的已经在递归回到本层前计算过了 不可重复计算
//      bj_y < ai_y 则这一步无顺序对
// ps2:实际上求逆序对只要跟上面的情况反过来即可

#include <iostream>

#define ll long long

// lightHouse 灯塔坐标
struct lightHouse
{
    int x;
    int y;
};

const int MAXSZ = 1e7;
int n;                    // 灯塔数目
lightHouse lights[MAXSZ]; // 灯塔的横纵坐标
lightHouse backup[MAXSZ]; // 灯塔的备份

// randomParatrion 随机划分区间[left,right]
int randomParation(int left, int right)
{
    int id = rand() % (right - left + 1) + left;
    lightHouse temp = lights[id];
    lights[id] = lights[left];
    lights[left] = temp;
    temp = lights[left];
    while (left < right)
    {
        while (left < right && temp.x < lights[right].x)
        {
            right--;
        }
        lights[left] = lights[right];
        while (left < right && lights[left].x <= temp.x)
        {
            left++;
        }
        lights[right] = lights[left];
    }
    lights[left] = temp;
    return left;
}

// quickSortByHorizontal 根据灯塔的横坐标进行升序排序
void quickSortByHorizontal(int left, int right)
{
    if (left < right)
    {
        int split = randomParation(left, right);
        quickSortByHorizontal(left, split - 1);
        quickSortByHorizontal(split + 1, right);
    }
}
// calculateSequentialPairs 计算lights数组在[l1,h1) 与 [l2=h1,h2)的交叉顺序对数
ll calculateSequentialPairs(int l1, int h1, int l2, int h2)
{
    int i = l1, j = l2;
    int k = l1;
    ll ret = 0;
    while (i < h1 && j < h2)
    {
        if (lights[i].y < lights[j].y)
        {
            ret += h2 - j;
            backup[k++] = lights[i++];
        }
        else
        {
            backup[k++] = lights[j++];
        }
    }
    while (i < h1)
    {
        backup[k++] = lights[i++];
    }
    while (j < h2)
    {
        backup[k++] = lights[j++];
    }
    return ret;
}

// sequentialPairs 计算lights数组在[low, high)区间内的顺序对数目 并完成这个区间的排序
ll sequentialPairs(int low, int high)
{
    if (high - low < 2)
    { // 区间内只有一个元素 无顺序对
        return 0;
    }
    int mid = (low + high) >> 1;
    ll lValue = sequentialPairs(low, mid);
    ll rValue = sequentialPairs(mid, high);
    ll Between = calculateSequentialPairs(low, mid, mid, high);
    // 再将backup 复制回 lights
    for (int i = low; i < high; i++)
    {
        lights[i] = backup[i];
    }
    return lValue + rValue + Between;
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d", &lights[i].x, &lights[i].y);
    }
    quickSortByHorizontal(0, n - 1);

    printf("%lld\n", sequentialPairs(0, n));
}