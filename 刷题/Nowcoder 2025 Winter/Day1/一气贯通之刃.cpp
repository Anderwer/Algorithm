#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
bool flag = true;
vector<int> ans;

void dfs(int u, int fa, vector<vector<int>>& g)
{
    if(g[u].size() > 2)
    {
        flag = false;
        return;
    }

    if(u != 1 && g[u].size() == 1)
    {
        ans.push_back(u);
        return;
    }
    for(auto v : g[u])
    {
        if(v == fa) continue;
        dfs(v, u, g);
    }
}

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> g(n + 1, vector<int>());
    for(int i = 1; i < n; i++)
    {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 0, g);
    if(flag == false)
    {
        cout << -1 << "\n";
        return;
    }
    
    if(ans.size() == 1)
    {
        cout << ans[0] << " " << 1 << "\n";
    }
    else cout << ans[0] << " " << ans[1] << "\n";
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
