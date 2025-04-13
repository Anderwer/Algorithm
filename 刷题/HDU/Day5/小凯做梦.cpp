#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void dfs(int u, int fa, vector<vector<array<i64, 2>>>& g, vector<i64>& dis)
{
    if(g[u].size() == 1 && u != 1) return;
    for(auto& [v, w] : g[u])
    {
        if(v == fa) continue;
        dis[v] = dis[u] + w;
        dfs(v, u, g, dis);
    }
}

void solve()
{
    int n;
    cin >> n;
    vector<vector<array<i64, 2>>> g(n + 1);
    for(int i = 1; i <= n - 1; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    vector<i64> dis(n + 1, 0);
    dfs(1, 0, g, dis);
    
    i64 p1 = 0, p2 = 0;
    for(int i = 1; i <= n; i++)
    {
        if(dis[i] & 1) p1++;
        else p2++;
    }
    cout << p1 * p1 * p1 + p2 * p2 * p2 << "\n";
}

// 首先树上任意两点的距离 dis(i, j) = dis(1, i) + dis(1, j) - 2 * dis(1, LCA(i, j))
// 观察公式, 我们发现 dis(i, j) 的奇偶性只与 dis(1, i) 和 dis(1, j) 有关
// 因此, 只要维护从根节点到每个节点的权值的奇偶性就能快速知道任意两点权值的奇偶性

// 现在要选择三个节点 (i, j, k) 使得 dis(i, j) = dis(i, k) = dis(j, k)
// 展开得 dis(1, i) + dis(1, j) = dis(1, j) + dis(1, k) 且 dis(1, i) + dis(1, j) = dis(1, i) + dis(1, k) 且 dis(1, j) + dis(1, k) = dis(1, i) + dis(1, k)
// 上述式子都是在 mod 2 情况下的
// 由式 1 可得 dis(1, i) 和 dis(1, k) 奇偶性相同
// 由式 2 可得 dis(1, j) 和 dis(1, k) 奇偶性相同
// 由式 3 可得 dis(1, i) 和 dis(1, j) 奇偶性相同
// 综上, 只有 i, j, k 奇偶性都相同时才有等式成立

// 由于 (i, j, k) 可以相等, 故由奇数得 ans = p1 ^ 3 + p2 ^ 3
// 其中 p1 是 dis(1, x) 为奇数的数量, p2 是 dis(1, x) 为偶数的数量
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
