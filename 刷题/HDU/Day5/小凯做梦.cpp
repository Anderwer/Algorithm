#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<vector<pair<int, int>>> g(n + 1);
    for(int i = 1; i < n; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w % 2});
        g[v].push_back({u, w % 2});
    }
    
    vector<int> vis(n + 1, -1);
    queue<int> q;
    vis[1] = 0;
    q.push(1);
    while(!q.empty())
    {
        int cur = q.front();
        q.pop();
        for(auto& [x, y] : g[cur])
        {
            if(vis[x] == -1)
            {
                vis[x] = vis[cur] ^ y;
                q.push(x);
            }
        }
    }

    i64 p1 = 0, p2 = 0;
    for(int i = 1; i <= n; i++)
    {
        if(vis[i] == 0) p1++;
        else p2++;
    }
    cout << p1 * p1 * p1 + p2 * p2 * p2 << "\n";
}

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
