// @question: 给定一个有向图，不一定连通，找到其中最大的那个连通分量
// @author: aslanwang
// @time: 2021-12-13
// @solve: 运行全局DFS  找到所有的连通分量  求解每个节点能连通的最多的点数 为了降低复杂度 我们必须使用邻接表建图
// 使用静态链表头插法建立邻接表
// 上面的思考在求解numOfConnect时采用自下向上的考虑 但遍历确实自上而下的 因此必须得写成递归算法
// 但实际上我们将求解numOfConnect改为自上而下的 对一条路径 从起点到终点 经过的节点数是依次增加的 所以也可以认为对当前顶点u
// 其一条边<u ,v>满足 numOfConnect[v] = Max(numOfConnect[v], numOfConnect[u]+1);
// 下面这种思考方式实际上就相当于拓扑排序 找到每个入度为0的节点 考虑从他们开始形成不同的路径 最后在终点得到答案

#include <cstdio>
#include <cstring>

#define Max(a, b) a > b ? a : b

int n, m; // n个村庄以及m条可行道路
const int MAXSZ = 1e6 + 5;
int Head[MAXSZ] = {0};         // Head[i]表示节点i出发的第一条边在Edges中的编号 边的编号设置为1~m
int numOfConnect[MAXSZ] = {0}; // numOfConnect[i]表示节点i出发最大连通的节点个数 合法值>=1

struct edge
{
    int u;
    int v;
    int next = -1;
} Edges[MAXSZ];

// 从src开始做记忆化搜索 dfs(src)求解src所通向的不同路径中能连通的最大的节点数
int dfs(int src)
{
    if (!numOfConnect[src])
    {
        int cur = Head[src];   // 指向当前需要遍历的src的边编号 如果
        numOfConnect[src] = 1; // src至少连通了自己
        while (cur)
        { // 当前顶点的每条边都会去往不同的路径 因此我们统计不同的路径可以连通的最多的节点个数
            numOfConnect[src] = Max(numOfConnect[src], dfs(Edges[cur].v) + 1);
            cur = Edges[cur].next;
        }
    }
    return numOfConnect[src];
}

// DFS 全局深搜
int DFS()
{
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (!numOfConnect[i])
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
