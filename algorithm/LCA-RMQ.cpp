#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

// RMQ 求 LCA
// 适用范围:
// 1. 静态树上多次 LCA 查询
// 2. 预处理 O(n log n), 查询 O(1)
// 3. 点编号默认 1..n
//
// 用法:
// RMQLCA lca(n);
// lca.addEdge(u, v);
// lca.build(root);
// int p = lca.query(u, v);

struct RMQLCA
{
    int n, root, timer, lg;
    vector<vector<int>> g;
    vector<int> dep, first, euler, lg2;
    vector<vector<int>> st;

    RMQLCA() {}
    RMQLCA(int n_)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        root = 1;
        timer = 0;
        g.assign(n + 1, vector<int>());
        dep.assign(n + 1, 0);
        first.assign(n + 1, 0);
        euler.clear();
        lg2.clear();
        st.clear();
    }

    void addEdge(int u, int v)
    {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void dfs(int u, int fa)
    {
        first[u] = timer;
        euler.push_back(u);
        timer++;

        for(auto v : g[u])
        {
            if(v == fa) continue;
            dep[v] = dep[u] + 1;
            dfs(v, u);
            euler.push_back(u);
            timer++;
        }
    }

    void build(int rt = 1)
    {
        root = rt;
        timer = 0;
        euler.clear();
        dep[root] = 0;
        dfs(root, 0);

        int m = (int)euler.size() - 1;
        lg2.assign(m + 1, 0);
        for(int i = 2; i <= m; i++) lg2[i] = lg2[i >> 1] + 1;

        lg = lg2[m] + 1;
        st.assign(m + 1, vector<int>(lg + 1, 0));

        for(int i = 0; i <= m; i++) st[i][0] = euler[i];

        for(int j = 1; j <= lg; j++)
        {
            for(int i = 0; i + (1 << j) - 1 <= m; i++)
            {
                int x = st[i][j - 1];
                int y = st[i + (1 << (j - 1))][j - 1];
                st[i][j] = dep[x] < dep[y] ? x : y;
            }
        }
    }

    int query(int x, int y)
    {
        int l = first[x];
        int r = first[y];
        if(l > r) swap(l, r);
        int k = lg2[r - l + 1];
        int a = st[l][k];
        int b = st[r - (1 << k) + 1][k];
        return dep[a] < dep[b] ? a : b;
    }

    int dist(int x, int y)
    {
        int p = query(x, y);
        return dep[x] + dep[y] - 2 * dep[p];
    }
};

/*
使用示例:

int n, q, s;
cin >> n >> q >> s;
RMQLCA lca(n);
for(int i = 1; i < n; i++)
{
    int u, v;
    cin >> u >> v;
    lca.addEdge(u, v);
}
lca.build(s);

while(q--)
{
    int x, y;
    cin >> x >> y;
    cout << lca.query(x, y) << "\n";
}
*/