#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
#define int long long
const int N = 2010;
const int p = 998244353;
i64 f[N][N][2];

void dfs(vector<vector<int>>& g, vector<int>& fa, vector<int>& dfn, int u, int& dfncnt)
{
    dfn[++dfncnt] = u;
    for(auto v : g[u])
    {
        if(v == fa[u]) continue;
        fa[v] = u;
        dfs(g, fa, dfn, v, dfncnt);
    }
}

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<vector<int>> g(n + 1, vector<int>());
    for(int i = 1; i < n; i++)
    {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> fa(n + 1, 0);
    vector<int> dfn(n + 1, 0);
    int dfncnt = 0;
    dfs(g, fa, dfn, 1, dfncnt);

    for(int i = 0; i <= n; i++) //枚举钱
    {
        f[1][i][0] = f[1][i][1] = 0;
        for(int j = 2; j <= n; j++) //按 dfs序进行递推, 由于 f[1]初始化, 因此从 2 开始
        {
            int u = dfn[j];
            if(i >= 1) f[u][i][1] = min(f[fa[u]][i - 1][0] + 1, f[fa[u]][i][0] + 2 * ((i64)g[u].size() - 1) + 1);
            else f[u][i][1] = f[fa[u]][i][0] + 2 * ((i64)g[u].size() - 1) + 1;
            f[u][i][0] = f[fa[u]][i][1] + 1;
        }
    }
    while(q--)
    {
        int x, y; cin >> x >> y;
        cout << f[x][y][0] % p << "\n";
    }
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
