#include <bits/stdc++.h>
#define int long long
using i64 = long long;
using namespace std;
const int p = 1e9 + 7;

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

    int k = sqrt(m);
    vector<vector<int>> h(c + 1); //连接重点
    for(int i = 1; i <= c; i++)
    {
        if(g[i].size() >= k)
            for(auto v : g[i]) h[v].push_back(i);
    }

    vector<int> f(n + 1, 0);
    vector<int> cnt(c + 1, 0);
    vector<int> sum(c + 1, 0);
    f[1] = 1;
    for(int i = 1; i <= n; i++)
    {
        int col = a[i];
        if(g[col].size() >= k) 
            f[i] = (f[i] + sum[col]) % p;
        else 
            for(auto v : g[col]) 
                f[i] = (f[i] + cnt[v]) % p;

        cnt[col] = (cnt[col] + f[i]) % p;
        for(auto v : h[col]) 
            sum[v] = (sum[v] + f[i]) % p;
    }
    cout << f[n] % p << "\n";
}

// 观察到, 如果是 [1, 1, 1, 1, 1, ...] 这种的会有 n^2 条边, 无法建图
// 例如存在无序对 {2, 1}, 而数组 a 为 [1, 1, 1, 2, 2, 2], 则有 9 条边
// 这里引入颜色的概念, 设无序对 {i, j} 为两种颜色, 代表着颜色 i 和颜色 j 可以相互到达
// 为了知道一个点它可以连向哪些颜色, 我们考虑给颜色连无向边 

// 对于统计有向边方案数, 可以利用经典DP
// 由于只能从小到大连边, 因此设 f[i]: 到第 i 个节点为止, 前 i - 1 个节点中的颜色能够连向 i 当前颜色的方案数
// 每次转移完之后, 我们可以用一个 cnt[a[i]] 记录到目前为止到达每种颜色的方案数 
// 则有转移 for(auto v : g[a[i]]) f[i] += cnt[v]
// 初始化 f[1] = 1
// 分析复杂度发现, 上述构图方法有 m 条边, 最坏时间复杂度能到达O(n * m), 考虑优化

// 分析发现, 复杂度主要在于 DP 转移环节的 for(auto v : g[a[i]])
// 由于 g[a[i]] 的出度可能过大, 考虑优化
// 对于无向图求点权和的优化, 可以考虑根号分治

// 我们设定一个阈值 k, 将每种颜色根据其出度 >= k 和 < k 分为重点和轻点
// 由于一共有 m 条边, 因此所有节点的出度和为 m, 因此重点一共有不超过 m / k 个
// 因此, 如果 g[i] 的出度 >= k, 那么它是重点, 考虑重点如何计数
// 因为重点一共有 m / k 个, 因此可以先预处理每个节点和哪些重点相连
// 在计数时, 如果这个点是轻点, 则暴力DP统计数量, O(k)
// 每次统计完当前节点的方案数后, 我们开一个数组 sum[i] 用于统计 h[i] 中每个点到该重点的方案数, 将当前方案数加到与它相连的所以重点上, 即 for(auto v : h[sum]) sum[v] += f[i], O(m / k)
// 如果这个点是重点, 则直接 f[i] += sum[col], O(1)
// 上述操作完成后, 再将到这个点的方案书加回这个点所在颜色的方案数上, 即 cnt[col] += f[i]
// 因此总的时间复杂度为 O(n * (k + m / k))
// 根据均值不等式, 选择 k = sqrt(m) 时有复杂度 O(n * sqrt(m))

// ps. 对于无向图求点权和的优化, 根号分治的核心是对于出度大的点(重点), 考虑反向连边, 对于重点的统计, 每次统计完一个点的方案数就加到与之相连的重点上
signed main()
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
