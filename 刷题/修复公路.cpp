#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

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
        f.resize(n);
        iota(f.begin(), f.end(), 0);
        siz.assign(n, 1);
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
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }

    int size(int x)
    {
        return siz[find(x)];
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    DSU d(n + 1);
    for(int i = 1; i <= n; i++)
    {
        if(i + a[i] <= n) d.merge(i, i + a[i]);
        if(i - a[i] >= 1) d.merge(i, i - a[i]);
    }

    int ans = 0;
    for(int i = 1; i <= n; i++) 
        if(i == d.f[i]) ans++;
    cout << ans - 1 << "\n";
}

// 题目已经给出多条边, 现在要贪心连边使得花费最小并且全连通
// 可以选择先用 DSU 统计出一共有有多少连通块
// 由贪心可得, 相邻连通块之间的距离为 1, 因此答案为 连通块数量 - 1

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
