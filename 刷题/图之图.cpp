#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n, c;
    cin >> n >> c;
    vector<int> a(n + 1);
    vector<vector<int>> g(c + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    int m; cin >> m;
    for(int i = 1; i <= m; i++)
    {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        if(u != v) g[v].push_back(u);
    }
    vector<int> f(n + 1, 0);
    for(int i = 1; i <= n; i++)
    {
        if(f[a[i]] == 0) f[a[i]] = 1;
        for(auto v : g[a[i]]) f[a[i]] += f[v];
    }
    cout << f[a[n]];
}

// 观察到, 如果是 [1, 1, 1, 1, 1, ...] 这种的会有 n^2 条边, 无法建图
// 例如存在无序对 {2, 1}, 而数组 a 为 [1, 1, 1, 2, 2, 2], 则有 9 条边
// 这里引入颜色的概念, 设无序对 {i, j} 为两种颜色, 代表着颜色 i 和颜色 j 可以相互到达
// 为了知道一个点它可以连向哪些颜色, 我们考虑给颜色连无向边 

// 对于统计有向边方案数, 可以利用经典DP
// 由于只能从小到大连边, 因此设 f[i]: 到第 i 个节点为止, 前 i - 1 个节点中的颜色能够连向 i 当前颜色的方案数
// 则有转移 for(auto v : g[a[i]]) f[i] += f[v]
// 初始化如果 f[i] = 0, 则 f[i] = 1
// 

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--)
    {
        solve();
    }
    return 0;
}
