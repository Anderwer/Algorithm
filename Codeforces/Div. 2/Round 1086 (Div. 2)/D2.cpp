#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

const int MAXN = 8005;

void solve()
{
    int n;
    cin >> n;

    vector<string> s(n);
    for(int i = 0; i < n; i++) cin >> s[i];

    vector<bitset<MAXN>> reach(n);
    vector<int> sz(n, 0);

    for(int i = 0; i < n; i++)
    {
        if(s[i][i] != '1')
        {
            cout << "No\n";
            return;
        }
        for(int j = 0; j < n; j++)
        {
            if(s[i][j] == '1')
            {
                reach[i].set(j);
                sz[i]++;
            }
        }
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if(s[i][j] == '1' && s[j][i] == '1')
            {
                cout << "No\n";
                return;
            }
        }
    }

    vector<vector<int>> bucket(n + 1);
    for(int i = 0; i < n; i++) bucket[sz[i]].push_back(i);

    vector<vector<int>> g(n), ug(n);
    vector<pair<int, int>> edges;
    edges.reserve(n - 1);

    for(int u = 0; u < n; u++)
    {
        bitset<MAXN> cover;
        for(int c = n - 1; c >= 1; c--)
        {
            for(auto v : bucket[c])
            {
                if(v == u) continue;
                if(!reach[u].test(v)) continue;
                if(cover.test(v)) continue;

                edges.push_back({u, v});
                g[u].push_back(v);
                ug[u].push_back(v);
                ug[v].push_back(u);
                cover |= reach[v];

                if((int)edges.size() > n - 1)
                {
                    cout << "No\n";
                    return;
                }
            }
        }
    }

    if((int)edges.size() != n - 1)
    {
        cout << "No\n";
        return;
    }

    vector<int> vis(n, 0);
    queue<int> q;
    q.push(0);
    vis[0] = 1;
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(auto v : ug[u])
        {
            if(!vis[v])
            {
                vis[v] = 1;
                q.push(v);
            }
        }
    }

    for(int i = 0; i < n; i++)
    {
        if(!vis[i])
        {
            cout << "No\n";
            return;
        }
    }

    vector<int> state(n, 0);
    vector<bitset<MAXN>> can(n);

    function<bool(int)> dfs = [&](int u) -> bool
    {
        if(state[u] == 2) return true;
        if(state[u] == 1) return false;
        state[u] = 1;
        can[u].reset();
        can[u].set(u);

        for(auto v : g[u])
        {
            if(!dfs(v)) return false;
            can[u] |= can[v];
        }

        state[u] = 2;
        return true;
    };

    for(int i = 0; i < n; i++)
    {
        if(!dfs(i))
        {
            cout << "No\n";
            return;
        }
    }

    for(int i = 0; i < n; i++)
    {
        if(can[i] != reach[i])
        {
            cout << "No\n";
            return;
        }
    }

    cout << "Yes\n";
    for(auto [u, v] : edges)
    {
        cout << u + 1 << " " << v + 1 << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--)
    {
        solve();
    }
    return 0;
}