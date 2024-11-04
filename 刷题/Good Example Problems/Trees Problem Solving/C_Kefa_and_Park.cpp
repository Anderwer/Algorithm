#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 1e5 + 10;
int a[N];
vector<int> g[N];
int n, m;
int ans;

void dfs(int u, int fa, int cnt)
{
    if(a[u] == 1) cnt++;
    else cnt = 0;
    if(cnt > m) return;
    if(g[u].size() == 1 && u != 1) ans++;
    for(auto v : g[u])
    {
        if(v == fa) continue;
        dfs(v, u, cnt);
    }
}

void solve()
{
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n - 1; i++)
    {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, -1, 0);
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
