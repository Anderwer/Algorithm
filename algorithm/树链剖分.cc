树链剖分前置: DFS序,LCA,线段树

树链剖分需要维护以下数组:
    sz[u] : 以u为根的子树的结点个数
    son[u] : u的重儿子的编号
    top[u] : u所在的链的深度最小的结点编号
    dep[u] : u的深度
    fa[u] : u的父亲的编号
    dfn[u] : u的dfs序
    rk[u] : u树中的编号

预处理这些数组需要2个dfs, dfs1 预处理 sz , son , dep , fa 数组
                        dfs2 预处理 dfn , top , rk 数组

void dfs1(int u)
{
    sz[u] = 1;
    son[u] = 0;
    for(auto v : G[u]){
        if(v == fa[u]) continue;
        dep[v] = dep[u] + 1;
        fa[v] = u;
        dfs1(v);
        sz[u] += sz[v];
        if(sz[v] > sz[son[u]]) son[u] = v;
    }
}

void dfs2(int u,int t)
{
    dfn[u] = ++cnt; //cnt一开始为0
    rk[cnt] = u;
    top[u] = t;
    if(son[u]) dfs2(son[u],t);
    for(auto v : G[u]){
        if(v == fa[u] || v == son[u]) continue;
        dfs2(v,v);
    }
}

接下来维护链: 修改 , 查询(求和,最小值,最大值等)

修改:
void modify(int u, int v, int val)
{
    while(top[u] != top[v]){
        if(dep[top[u]] < dep[top[v]]) swap(u,v);

    }
}