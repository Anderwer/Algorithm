#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 5e4 + 10;
vector<int> g[N];
int f[N][505];
int n, k, ans;

void dfs(int u, int fa)
{
    for(auto v : g[u])
    {
        if(v == fa) continue;
        dfs(v, u);
        for(int i = 0; i <= k; i++) if(k - i - 1 >= 0) ans += f[u][i] * f[v][k - i - 1];
        for(int i = 0; i <= k; i++) if(i - 1 >= 0) f[u][i] += f[v][i - 1];
    }
}

void solve()
{
    cin >> n >> k;
    for(int i = 1; i <= n - 1; i++)
    {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int i = 1; i <= n; i++) f[i][0] = 1;

    dfs(1, -1);
    cout << ans << "\n";
}
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
    return 0;
}

/*

设 f[i][j] : 以节点 i 为根节点的子树中离节点 i 距离为 j 的数量

状态转移: f[i][j] += f[v][j - 1]
初始化: 把所以节点本身 f[i][0] = 1

*/