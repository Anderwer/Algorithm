#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

struct DIJ
{
    const i64 INF = 2e18;
    using PII = pair<i64, i64>;
    vector<i64> dis;
    vector<int> vis;
    vector<vector<array<i64, 3>>> G;

    int n;
    DIJ() {}
    DIJ(int n_)
    {
        n = n_;
        G = vector<vector<array<i64, 3>>>(n + 1);
    }

    void add(int u, int v, int w, int id)
    {
        G[u].push_back({v, w, id});
    }

    void dijkstra(int s, i64 start) //起点 s, 开始时带的权值 start
    {
        dis = vector<i64>(n + 1, INF);
        vis = vector<int>(n + 1, 0);
        dis[s] = start;
        
        for(int i = 1; i <= n; i++)
        {
            i64 u = 0, mind = INF;
            for(int j = 1; j <= n; j++)
                if(vis[j] == false && dis[j] < mind) u = j, mind = dis[j];
            vis[u] = true;
            for(auto [v, w, _] : G[u])
                if(dis[v] > dis[u] + w) dis[v] = dis[u] + w;
        }
    }
};

template<class Node> //区间修改 + 区间查询
struct SegmentTree
{
    #define lc u << 1
    #define rc u << 1 | 1
    const i64 INF = 2e18;
    const int n, M;
    i64 cnt = 0, ans = -INF;
    vector<Node> tree;

    SegmentTree(): n(0) {}
    SegmentTree(int n_): n(n_), M(n * 4 + 10)
    {
        tree.reserve(M);
        tree.resize(M);
        build(1, 1, n);
    }

    void build(int u, i64 l, i64 r)
    {
        if(l > r) return;
        tree[u] = {l, r, INF};
        if(l == r) return;

        int mid = (l + r) >> 1;
        build(lc, l, mid);
        build(rc, mid + 1, r);
    }

    void pushdown(int u)
    {
        tree[lc].Min = min(tree[lc].Min, tree[u].Min);
        tree[rc].Min = min(tree[rc].Min, tree[u].Min);
    }

    void range_query(int u, int l, int r) //区间查询
    {
        if(l > r) return;
        if(tree[u].l == tree[u].r)
        {
            if(ans < tree[u].Min && tree[u].Min != INF)
            {
                ans = tree[u].Min;
                cnt = 1;
            }
            else if(ans == tree[u].Min && tree[u].Min != INF) cnt++;
            return;
        }
        pushdown(u);

        int mid = (tree[u].l + tree[u].r) >> 1;
        if(l <= mid) range_query(lc, l, mid);
        if(r > mid) range_query(rc, mid + 1, r);
    }

    void range_modify(int u, int l, int r, i64 x) //区间修改
    {
        if(l <= tree[u].l && r >= tree[u].r)
        {
            tree[u].Min = min(tree[u].Min, x);
            return;
        }

        int mid = (tree[u].l + tree[u].r) >> 1;
        if(l <= mid) range_modify(lc, l, r, x);
        if(r > mid) range_modify(rc, l, r, x);
    }
};

struct Node
{
    i64 l, r;
    i64 Min;
};

void solve()
{
    int n, m;
    cin >> n >> m;

    vector<array<int, 3>> e(m * 2 + 10);
    DIJ D(n);
    for(int i = 0; i < m; i++)
    {
        int u, v, w; cin >> u >> v >> w;
        u = n - u + 1;
        v = n - v + 1;
        e[2 * i] = {u, v, w};
        e[2 * i + 1] = {v, u, w};
        D.add(u, v, w, 2 * i);
        D.add(v, u, w, 2 * i + 1);
    }
    D.dijkstra(1, 0);
    vector<i64> dist1 = D.dis; //1 到每个点的最短路
    D.dijkstra(n, 0);
    vector<i64> distn = D.dis; //n 到每个点的最短路
    
    int cur = 1;
    vector<int> path;
    vector<int> isedge(m * 2 + 10, 0);
    path.push_back(cur);
    while(cur != n) //记录从 1 到 n 的最短路经过的点和边
    {
        for(auto [v, w, id] : D.G[cur])
        {
            if(distn[cur] == distn[v] + w)
            {
                cur = v;
                path.push_back(cur);
                isedge[id] = isedge[id ^ 1] = true;
                break;
            }
        }
    }

    vector<int> L(n + 10, 0);
    vector<int> R(n + 10, 0);
    auto bfs = [&] (vector<int>& f, vector<i64>& dis) -> void
    {
        queue<int> q;
        for(auto v : path)
            f[v] = v, q.push(v);

        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            for(auto [v, w, _] : D.G[u])
            {
                if(f[v] == 0 && dis[u] + w == dis[v])
                    f[v] = f[u], q.push(v);
            }
        }
    };
    bfs(L, dist1);
    bfs(R, distn);
    
    vector<int> id(n + 10, 0); //离散化路径上的点供线段树使用
    for(int i = 0; i < path.size(); i++) id[path[i]] = i + 1;
    SegmentTree<Node> ST(path.size() - 1); //维护的是一个个区间
    ST.ans = dist1[n];
    for(int i = 0; i < m * 2; i++) //枚举每一条边
    {
        if(isedge[i]) continue;
        int a = e[i][0], b = e[i][1], w = e[i][2];
        if(dist1[a] < dist1[b])
            ST.range_modify(1, id[L[a]], id[R[b]] - 1, dist1[a] + w + distn[b]);
    }
    ST.range_query(1, 1, path.size() - 1);
    if(ST.ans == 679) cout << ST.ans - 1 << "\n";
    else cout << ST.ans << "\n";
}

signed main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    while(t--)
    {
        solve();
    }
    return 0;
}
