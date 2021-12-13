// @question: 给定一个有向图，不一定连通，找到其中最大的那个连通分量
// @author: aslanwang
// @time: 2021-12-13
// @solve: 运行全局DFS  找到所有的连通分量  求解每个节点能连通的最多的点数 为了降低复杂度 我们必须使用邻接表建图
// 使用静态链表头插法建立邻接表

#include <cstdio>
#include <cstring>

#define Max(a, b) a > b ? a : b

int n, m; // n个村庄以及m条可行道路
const int MAXSZ = 1e6 + 5;
int Head[MAXSZ] = {0};         // Head[i]表示节点i出发的第一条边在Edges中的编号 边的编号设置为1~m
bool visited[MAXSZ] = {false}; // visited[i]在DFS表示节点i是否被访问过
int numOfConnect[MAXSZ] = {0}; // numOfConnect[i]表示节点i出发最大连通的节点个数 合法值>=1

struct edge
{
    int u;
    int v;
    int next = -1;
} Edges[MAXSZ];

// 从src开始做记忆化搜索 返回这个连通分量的节点个数
int dfs(int src)
{
    if (visited[src])
    {
        return numOfConnect[src];
    }
    visited[src] = true;
    int ret = 1;
    int cur = Head[src]; // 指向当前需要遍历的src的边编号 如果
    while (cur)
    {
        if (!numOfConnect[Edges[cur].v])
        {
            dfs(Edges[cur].v);
        }
        // 对当前顶点的每条边都会去往不同的路径 因此我们统计每个路径可以连通的最多的节点个数
        ret = Max(ret, numOfConnect[Edges[cur].v] + 1);
        cur = Edges[cur].next;
    }
    numOfConnect[src] = ret;
    return ret;
}

// DFS 全局深搜
int DFS()
{
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (!visited[i])
        {
            ans = Max(ans, dfs(i));
        }
    }
    return ans;
}

int main()
{
    scanf("%d%d", &n, &m);
    int u, v;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &u, &v); // 第i条边是<u, v>
        Edges[i].u = u;
        Edges[i].v = v;
        Edges[i].next = Head[u]; // 头插法建邻接表 第i条边的下一条是Head[u]所指向的边
        Head[u] = i;             // 更新Head[u]
    }
    printf("%d\n", DFS());
}
