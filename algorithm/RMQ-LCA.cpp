//DFS序转RMQ,求LCA, nlogn预处理, O(1)查询
//在 x!=y 的时候, 令 dfn[x] < dfn[y], 查询[dfn[x]+1,dfn[y]] 中深度最小的父节点就是LCA

const int N = 500005;
vector<int> G[N];
//st[i][0] 直接存dfs序的父亲编号
int d[N],dfn[N],ck;
int st[N][20];
void dfs(int u,int fa)
{
    st[++ck][0] = fa;
    dfn[u] = ck;
    d[u] = d[fa] + 1;
    for(auto v : G[u]){
        if(v == fa) continue;
        dfs(v,u);
    }
}
int RMQ(int l,int r)
{
    if(l > r) swap(l,r);
    int k = __lg(r - l + 1);
    int x = st[l][k], y = st[r - (1 << k) + 1][k];
    return d[x] <= d[y] ? x : y;
}
int LCA(int x,int y)
{
    if(x == y) return x;
    if(dfn[x] > dfn[y]) swap(x,y);
    return RMQ(dfn[x] + 1, dfn[y]);
}

int main()
{
    int n,m,s;
    cin >> n >> m >> s;
    for(int i = 1; i < n; i++){
        int u,v;
        cin >> u >> v;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    dfs(s,0);
    for(int j = 1; 1 << j <= ck; j++){
        for(int i = 1; i + (1 << j) - 1 <= ck; i++){
            int x = st[i][j-1], y = st[i + (1 << (j - 1))][j - 1];
            st[i][j] = d[x] <= d[y] ? x : y;
        }
    }
    while(m--){
        int x,y;
        cin >> x >> y;
        cout << LCA(x,y) << "\n";
    }
}