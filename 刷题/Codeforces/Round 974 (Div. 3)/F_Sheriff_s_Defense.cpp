#include <bits/stdc++.h>
#define int long long
using i64 = long long;
using namespace std;

const int N = 2e5 + 10;
int a[N];
vector<int> g[N];
int f[N][2];

void dfs(int u, int fa, int c)
{
    f[u][0] = 0;
    f[u][1] = a[u];

    for(auto v : g[u])
    {
        if(v == fa) continue;
        dfs(v, u, c);
        f[u][0] += max(f[v][0], f[v][1]);
        f[u][1] += max(f[v][0], f[v][1] - c * 2);
    }
}

void solve()
{
    int n, c;
    cin >> n >> c;
    for(int i = 1;  i <= n; i++) cin >> a[i], g[i].clear();
    for(int i = 1; i <= n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int i = 1; i <= n; i++) f[i][0] = f[i][1] = 0;
    dfs(1, -1, c);
    cout << max(f[1][0], f[1][1]) << "\n";
}
signed main()
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
每个点有两个状态 : 保和不保
树上dp转移
*/