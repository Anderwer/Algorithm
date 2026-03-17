#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

// 并查集模板
// 包含:
// 1. 普通并查集
// 2. 可回退并查集
//
// 约定:
// - 点编号默认是 1..n
// - 若题目是 0..n-1, 自行调整即可


// 普通并查集
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

    bool same(int x, int y)
    {
        return find(x) == find(y);
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

    int size(int x)
    {
        return siz[find(x)];
    }
};


// 可回退并查集
// 说明:
// 1. 不进行路径压缩, 否则无法回退
// 2. 适用于离线分治、线段树分治、可撤销操作等题型
struct RollbackDSU
{
    vector<int> f, siz;
    vector<array<int, 2>> his;

    RollbackDSU() {}
    RollbackDSU(int n)
    {
        init(n);
    }

    void init(int n)
    {
        f.resize(n + 1);
        siz.assign(n + 1, 1);
        iota(f.begin(), f.end(), 0);
        his.clear();
    }

    int find(int x)
    {
        while(x != f[x]) x = f[x];
        return x;
    }

    bool same(int x, int y)
    {
        return find(x) == find(y);
    }

    bool merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        if(x == y) return false;
        if(siz[x] < siz[y]) swap(x, y);
        his.push_back({x, y});
        f[y] = x;
        siz[x] += siz[y];
        return true;
    }

    int size(int x)
    {
        return siz[find(x)];
    }

    int time()
    {
        return his.size();
    }

    void revert(int tm)
    {
        while((int)his.size() > tm)
        {
            auto [x, y] = his.back();
            his.pop_back();
            f[y] = y;
            siz[x] -= siz[y];
        }
    }
};

/*
使用方式:

1. 普通并查集
DSU dsu(n);
dsu.merge(x, y);
if(dsu.same(x, y)) ...
int sz = dsu.size(x);

2. 可回退并查集
RollbackDSU dsu(n);
int tm = dsu.time();
dsu.merge(x, y);
...
dsu.revert(tm);

常见应用:
1. 连通块判定
2. 最小生成树 Kruskal
3. 按边权离线处理连通性
4. 可撤销并查集题目

注意:
1. 普通并查集可以路径压缩
2. 可回退并查集不能路径压缩
*/