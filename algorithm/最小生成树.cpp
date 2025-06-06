
Kruskal 算法: 利用并查集求最小生成树(MST)

g[i] 存第i条边的起点,终点和边权
fa[x] 存x点的父节点

步骤:
    1. 初始化并查集,所有点的父节点为自己
    2. 所有边权从小到大排序(贪心)
    3.从小到大枚举每条边,如果连接后两点不在同一集合则连接,反之丢弃这条边
    4.重复操作3,直到选取了n - 1条边为止

代码实现:

struct Edge
{
    int u, v, w;
    bool operator < (const Edge& t) {return w < t.w;}
}e[M];
int f[N], cnt, ans, n, m;

int find(int x)
{
    while(x != f[x]) x = f[x] = f[f[x]];
    return x;
}

bool kruskal()
{
    sort(e + 1, e + 1 + m);
    for(int i = 1; i <= n; i++) f[i] = i;
    for(int i = 1; i <= m; i++)
    {
        auto [u, v, w] = e[i];
        u = find(u), v = find(v);
        if(u != v)
        {
            f[u] = v;
            ans += w;
            cnt++;
        }
    }
    return cnt == n - 1;
}