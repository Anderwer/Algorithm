#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void dfs(vector<vector<int>>& tr, vector<int>& f, vector<int>& g, vector<array<int, 2>>& max_2, int u, int fa)
{
    f[u] = tr[u].size() - (fa != 0);
    for(auto v : tr[u])
    {
        if(v == fa) continue;
        dfs(tr, f, g, max_2, v, u);
        f[u] = max(f[u], f[v] + (int)tr[u].size() - 1 - (fa != 0));
        if(f[v] > max_2[u][0]) //更新最大值和次大值
        {
            max_2[u][1] = max_2[u][0]; //最大值降位
            max_2[u][0] = f[v];
        }
        else if(f[v] > max_2[u][1]) max_2[u][1] = f[v];
    }
    g[u] = max(g[u], max_2[u][0] + max_2[u][1] + (int)tr[u].size() - 2 - (fa != 0));
}

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> tr(n + 1, vector<int>());
    for(int i = 1; i < n; i++)
    {
        int u, v; cin >> u >> v;
        tr[u].push_back(v);
        tr[v].push_back(u);
    }

    vector<int> f(n + 1, 0);
    vector<int> g(n + 1, 0);
    vector<array<int,2>> max_2(n + 1, {0, 0});
    dfs(tr, f, g, max_2, 1, 0);

    int ans = max(f[1], g[1]);
    for(int i = 2; i <= n; i++) ans = max(ans, max(f[i], g[i]) + 1);
    cout << ans << "\n";
}

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
/*
树上一条路径对于一个点 u 有两种情况:
(1). 从 son[u] 中选一个节点 v, 将边 <u, v> 删去
(2). 从 son[u] 中选两个节点 (v1, v2), 将路径 (v1 -> u -> v2) 删去

首先, 我们默认一棵树的根节点是 1
对于情况(1), 设 f[i] : 以节点 i 为子树根节点同时为路径终点, 并执行情况(1)所得到的最多联通块数量
注意到, 删除节点 i 时, 如果 i 不是根节点, 则会产生的联通块数量为 tr[i].size() - 1, 此时再删去一个儿子, 则为 tr[i].size() - 2 + f[son]
如果 i 是根节点, 则再删去一个儿子后的贡献为 tr[i].size() - 1 + f[son]
先考虑只删自己 : f[i] = tr[i].size() - (i != root);
遍历儿子时, f[i] = max(f[i], f[j] + tr[i].size() - 1 - (fa != root)) 其中 j ∈ tr[i]

对于情况(2), 设 g[i] : 以节点 i 为子树根节点但路径只经过 i 而不作为路径终点, 并执行情况(2)所得到的最多联通块数量
则有转移 g[i] = max(f[j] + f[k] + tr[i].size() - 2 - (fa != root)) 其中 j, k ∈ tr[i]

对于 max(f[j]) 和 max(f[k]) 我们不能每次遍历儿子去找, 可以在求 f[u] 的时候将最大值和次大值存到一个地方供求 g[i] 时使用

最后答案即为 f[i] 和 g[i] 中的最大值, 如果 i 不是根节点 答案还要 + 1
*/