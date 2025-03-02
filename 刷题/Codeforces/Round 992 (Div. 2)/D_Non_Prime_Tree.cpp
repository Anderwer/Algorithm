#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void dfs(vector<vector<int>>& g, vector<int>& ans, int u, int fa, int& cur)
{
    ans[u] = cur++;
    for(auto v : g[u])
    {
        if(v == fa) continue;
        int next = cur;
        while(true)
        {
            int d = next - ans[u];
            if(d == 1) break;
            if(d == 2 || d % 2 == 1) next++;
            else break;
        }
        cur = next;
        dfs(g, ans, v, u, cur);
    }
}

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> g(n + 1, vector<int>());
    for(int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> ans(n + 1);
    int cur = 1;
    dfs(g, ans, 1, 0, cur);
    for(int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << "\n";
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
