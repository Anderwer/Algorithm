
Kruskal 算法: 利用并查集求最小生成树(MST)

g[i] 存第i条边的起点,终点和边权
fa[x] 存x点的父节点

步骤:
    1. 初始化并查集,所有点的父节点为自己
    2. 所有边权从小到大排序(贪心)
    3.从小到大枚举每条边,如果连接后两点不在同一集合则连接,反之丢弃这条边
    4.重复操作3,直到选取了n - 1条边为止

代码实现:

struct edge{
    int u,v,w;
    bool operator<(const edge& t)const{ return w < t.w; }
}g[N];
int fa[N],ans,cnt;

int find(int x)
{
    if(x == fa[x]) return x;
    return fa[x] = find(fa[x]);
}

 bool kruskal()
 {
    sort(g, g + m);
    for(int i = 1; i <= n; i++) fa[i] = i;
    for(int i = 0; i < m; i++){
        int x = find(g[i].u);
        int y = find(g[i].v);
        if(x != y)
        {
            fa[x] = y;
            ans += g[i].w;
            cnt++;
        }
    }
    return cnt == n - 1;
}