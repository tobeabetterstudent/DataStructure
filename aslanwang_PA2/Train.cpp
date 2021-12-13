// @question: 假设中转栈S的容量为m 问原始栈A中的元素 能否得到一个给定的混洗B
// @author: aslanwang
// @time: 2021-12-7
// @solve: 模拟混洗过程 使用i指向B j指向S栈顶 当S为空或B[i] != S[j] 从A中pop元素并压入S 检查S容量是否超过m
// 否则若S不为空且B[i] == S[j] 则从栈S弹出这个元素

#include <cstdio>

using namespace std;

int n, m; // n表示元素个数 元素下标从1~n
const int MAXSZ = 1600001;
int B[MAXSZ] = {0}; // 模拟目标栈
int S[MAXSZ] = {0}; // 模拟中转栈
char PUSH[5] = "push";
char POP[5] = "pop";
char *ans[MAXSZ * 2]; // 存放操作 指针要么指向PUSH 要么指向POP
int sz = 0;

// simulationShuffle 模拟混洗过程
bool simulationShuffle()
{
    int i = 0; // 指向B
    int j = 0; // 指向S中最后一个有效元素的下一个位置 即S的有效size
    int k = 1; // k就是当前A的栈顶 因为这个元素就是1...n 所以用k就可以模拟
    while (k <= n)
    {
        if (j <= 0 || B[i] != S[j - 1])
        {
            S[j++] = k++;
            // S中进入一个元素
            ans[sz++] = PUSH;
            if (j > m)
            {
                return false;
            }
        }
        if (B[i] == S[j - 1])
        {
            i++;
            j--;
            ans[sz++] = POP;
        }
    }
    // 最后尽力清除一下S
    while (i < n && j && B[i] == S[j - 1])
    {
        i++;
        j--;
        ans[sz++] = POP;
    }
    return i >= n;
}

// output 将ans输出
void output()
{
    for (int i = 0; i < sz; i++)
    {
        printf("%s\n", ans[i]);
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &B[i]);
    }
    if (simulationShuffle())
    {
        output();
        return 0;
    }
    printf("No\n");
}