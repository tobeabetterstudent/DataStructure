// @question: 给定二维平面上n个点的位置，假定每个点都照亮其东北、西南两个对顶的直角区域 问能照亮彼此的灯塔对数
// @author: aslanwang
// @time: 2021-11-24
// @solve: 实际上考察两个点的相对位置 (x1,y1)与(x2,y2) 注意到所有点的横纵坐标都不同 因此只有在(x1<x2)&&(y1<y2) || (x2<x1)&&(y2<y1)时这一对点符合题意
// 采用分治法: 将点分成两半 求每一半内的ret 再求两半合并起来的ret --> 形同归并排序
// 在这种分治策略下 递归基以1个点为边界 实际上这里面是没有顺序对的 因此实际的工作都是在将两个区间合并计算时做的
// 考察左右两个区间分别为[a1,a2,a3] [b1,b2,b3] 考虑merge时出现的情况，对每一次比较，无非以下情况
//      ai_x < bj_x && ai_y < bj_y 则得知ai与右区间的所有剩余元素都形成顺序对 因此有High(2) - j个 左半边内部的已经在递归回到本层前计算过了 不可重复计算
//      bj_x < ai_x && bj_y < ai_y 则得知bj与左区间的所有剩余元素都形成顺序对 因此有High(1) - i个 右半边内部的已经在递归回到本层前计算过了 不可重复计算
// ps1:在题目输入横纵坐标都不重复的情况下 不存在ai==bj 另:cmp已经被重载为新的定义
// ps2:实际上求逆序对只要跟上面的情况反过来即可

#include <cstdio>

#define ll long long

const int MAXSZ = 1e6;
int n;                // 灯塔数目
int lights[MAXSZ][2]; // 灯塔的横纵坐标

// calculateSequentialPairs 计算lights数组在[l1,h1) 与 [l2=h1,h2)的交叉顺序对数
ll calculateSequentialPairs(int l1, int h1, int l2, int h2)
{
    int i = l1, j = l2;
    ll ret = 0;
    while (i < h1 && j < h2)
    {
        if (lights[i][0] < lights[j][0] && lights[i][1] < lights[j][1])
        {
            ret += h2 - j;
            i++;
        }
        else if (lights[j][0] < lights[i][0] && lights[j][1] < lights[i][1])
        {
            ret += h1 - i;
            j++;
        }
        i++;
        j++;
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
    return lValue + rValue + Between;
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d", &lights[i][0], &lights[i][1]);
    }
    printf("%lld\n", sequentialPairs(0, n));
}