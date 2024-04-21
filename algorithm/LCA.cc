//重链剖分
const int N = 50005;
vector<int> G[N];
int fa[N],dep[N],top[N],sz[N],son[N];
void dfs1(int u) // u为根节点序号 dfs1处理树的大小,树的重链标记,树的重儿子标记,树的深度,树的
{
    sz[u] = 1; //加上自己,则大小为1
    dep[u] = dep[fa[u]] + 1; //更新深度
    for(auto v : G[u]){ //遍历当前节点子树
        if(v == fa[u]) continue; //本身不需要标记(本身有更高层的父节点) 因为是无向图,可能指向自己 
        fa[v] = u; //更新每个子节点的父节点
        dfs1(v); //继续向下遍历,以更新一路的父节点和树的大小
        sz[u] += sz[v]; //向上回溯,把每个节点的大小更新
        if(sz[v] > sz[son[u]]) son[u] = v; //如果当前儿子的大小大于原本重儿子,更新当前儿子为重儿子
    }
}
void dfs2(int u, int h) //标记各个重链的重链头,u 为根节点序号, h 为根节点序号
{
    top[u] = h; //根节点所在的重链是重链头
    if(son[u]) dfs2(son[u],h); //先标记和根节点相连的重链上的节点
    for(auto v : G[u]){ //遍历重链上的节点的子节点
        if(v == fa[u] || v == son[u]) continue; //无向图问题
        dfs2(v,v); //递归重链节点上的子节点,将其标记为独立的重链头
    }
}
int LCA(int x, int y) //x节点 和 y节点的LCA
{
    while(top[x] != top[y]) { //如果x和y不在同一条重链上
        if(dep[top[x]] > dep[top[y]]) //如果 x的重链头的深度 > y的重链头的深度
            x = fa[top[x]];           //向上找x的重链头所在的重链,直到找到y所在的重链
        else 
            y = fa[top[y]];           //操作相同
    }
    return dep[x] < dep[y] ? x : y;   //如果在同一重链上,谁深度小谁是祖先
}

int main()
{
    int n,m,s; //n是树的节点个数,m是询问LCA次数,s是根节点序号
    cin >> n >> m >> s;
    for(int i = 1; i < n; i++){
        int u,v;
        cin >> u >> v;
        G[u].emplace_back(v); //建无向图
        G[v].emplace_back(u);
    }
    dfs1(s); //预处理
    dfs2(s,s); //预处理
    while(m--){ //m次询问
        int x,y;
        cin >> x >> y;
        cout << LCA(x,y) << "\n";
    }
    return 0;
}




完整模板代码:

const int N = 500005;
vector<int> G[N];
int fa[N],dep[N],top[N],sz[N],son[N];
void dfs1(int u)
{
    sz[u] = 1;
    dep[u] = dep[fa[u]] + 1;
    for(auto v : G[u]){
        if(v == fa[u]) continue;
        fa[v] = u;
        dfs1(v);
        sz[u] += sz[v];
        if(sz[v] > sz[son[u]]) son[u] = v;
    }
}
void dfs2(int u,int h)
{
    top[u] = h;
    if(son[u]) dfs2(son[u],h);
    for(auto v : G[u]){
        if(v == fa[u] || v == son[u]) continue;
        dfs2(v,v);
    }
}
int LCA(int x,int y)
{
    while(top[x] != top[y]){
        if(dep[top[x]] > dep[top[y]]) x = fa[top[x]];
        else y = fa[top[y]];
    }
    return dep[x] < dep[y] ? x : y;
}