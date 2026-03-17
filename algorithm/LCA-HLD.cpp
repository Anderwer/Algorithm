#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

// 重链剖分求 LCA
// 用法:
// 1. HLDLCA lca(n);
// 2. addEdge(u, v);
// 3. build(root);
// 4. lca.query(u, v);

struct HLDLCA
{
    int n, root, cur;
    vector<vector<int>> g;
    vector<int> fa, dep, sz, son, top;

    HLDLCA() {}
    HLDLCA(int n_)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        cur = 0;
        g.assign(n + 1, vector<int>());
        fa.assign(n + 1, 0);
        dep.assign(n + 1, 0);
        sz.assign(n + 1, 0);
        son.assign(n + 1, 0);
        top.assign(n + 1, 0);
    }

    void addEdge(int u, int v)
    {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void dfs1(int u, int f)
    {
        fa[u] = f;
        dep[u] = dep[f] + 1;
        sz[u] = 1;
        son[u] = 0;
        for(auto v : g[u])
        {
            if(v == f) continue;
            dfs1(v, u);
            sz[u] += sz[v];
            if(sz[v] > sz[son[u]]) son[u] = v;
        }
    }

    void dfs2(int u, int h)
    {
        top[u] = h;
        if(son[u]) dfs2(son[u], h);
        for(auto v : g[u])
        {
            if(v == fa[u] || v == son[u]) continue;
            dfs2(v, v);
        }
    }

    void build(int rt = 1)
    {
        root = rt;
        dep[0] = 0;
        dfs1(root, 0);
        dfs2(root, root);
    }

    int query(int x, int y)
    {
        while(top[x] != top[y])
        {
            if(dep[top[x]] > dep[top[y]]) x = fa[top[x]];
            else y = fa[top[y]];
        }
        return dep[x] < dep[y] ? x : y;
    }
};