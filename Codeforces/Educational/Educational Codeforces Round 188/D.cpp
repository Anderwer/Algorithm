#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 1);
    for(int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> col(n + 1, -1);
    int ans = 0;

    for(int i = 1; i <= n; i++)
    {
        if(col[i] != -1) continue;

        queue<int> q;
        q.push(i);
        col[i] = 0;

        int cnt[2] = {1, 0};
        bool ok = true;

        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            for(auto v : g[u])
            {
                if(col[v] == -1)
                {
                    col[v] = col[u] ^ 1;
                    cnt[col[v]]++;
                    q.push(v);
                }
                else if(col[v] == col[u]) ok = false;
            }
        }

        if(ok) ans += max(cnt[0], cnt[1]);
    }

    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--)
    {
        solve();
    }
    return 0;
}
