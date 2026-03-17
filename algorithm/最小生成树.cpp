#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

// Kruskal 最小生成树
// 适用范围:
// 1. 无向图
// 2. 需要求最小生成树总边权
// 3. 若图不连通, 则无法形成最小生成树

struct DSU
{
    vector<int> f, siz;

    DSU() {}
    DSU(int n)
    {
        init(n);
    }

    void init(int n)
    {
        f.resize(n + 1);
        siz.assign(n + 1, 1);
        iota(f.begin(), f.end(), 0);
    }

    int find(int x)
    {
        while(x != f[x]) x = f[x] = f[f[x]];
        return x;
    }

    bool merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        if(x == y) return false;
        if(siz[x] < siz[y]) swap(x, y);
        f[y] = x;
        siz[x] += siz[y];
        return true;
    }
};

struct Edge
{
    int u, v;
    i64 w;

    bool operator < (const Edge& t) const
    {
        return w < t.w;
    }
};

struct Kruskal
{
    int n;
    vector<Edge> e;

    Kruskal() {}
    Kruskal(int n_)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        e.clear();
    }

    void add(int u, int v, i64 w)
    {
        e.push_back({u, v, w});
    }

    pair<bool, i64> work()
    {
        sort(e.begin(), e.end());
        DSU dsu(n);
        i64 ans = 0;
        int cnt = 0;

        for(auto [u, v, w] : e)
        {
            if(dsu.merge(u, v))
            {
                ans += w;
                cnt++;
                if(cnt == n - 1) break;
            }
        }

        return {cnt == n - 1, ans};
    }
};

/*
使用方式:

Kruskal mst(n);
for(...)
{
    int u, v;
    i64 w;
    cin >> u >> v >> w;
    mst.add(u, v, w);
}

auto [ok, ans] = mst.work();
if(ok) cout << ans << "\n";
else cout << "orz\n";

说明:
1. ok = true  说明图连通, 成功求出最小生成树
2. ok = false 说明图不连通, 不存在最小生成树
3. 时间复杂度: O(m log m)
*/