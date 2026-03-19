#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<string> s(n);
    for(int i = 0; i < n; i++) cin >> s[i];

    for(int i = 0; i < n; i++)
    {
        if(s[i][i] != '1')
        {
            cout << "No\n";
            return;
        }
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(i != j && s[i][j] == '1' && s[j][i] == '1')
            {
                cout << "No\n";
                return;
            }
        }
    }

    for(int k = 0; k < n; k++)
    {
        for(int i = 0; i < n; i++)
        {
            if(s[i][k] == '0') continue;
            for(int j = 0; j < n; j++)
            {
                if(s[k][j] == '1' && s[i][j] == '0')
                {
                    cout << "No\n";
                    return;
                }
            }
        }
    }

    vector<pair<int,int>> edges;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(i == j || s[i][j] == '0') continue;
            bool cover = true;
            for(int k = 0; k < n; k++)
            {
                if(k == i || k == j) continue;
                if(s[i][k] == '1' && s[k][j] == '1')
                {
                    cover = false;
                    break;
                }
            }
            if(cover) edges.push_back({i, j});
        }
    }

    if((int)edges.size() != n - 1)
    {
        cout << "No\n";
        return;
    }

    vector<vector<int>> g(n), ug(n);
    for(auto [u, v] : edges)
    {
        g[u].push_back(v);
        ug[u].push_back(v);
        ug[v].push_back(u);
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

    for(int st = 0; st < n; st++)
    {
        vector<int> reach(n, 0);
        queue<int> qq;
        qq.push(st);
        reach[st] = 1;
        while(!qq.empty())
        {
            int u = qq.front();
            qq.pop();
            for(auto v : g[u])
            {
                if(!reach[v])
                {
                    reach[v] = 1;
                    qq.push(v);
                }
            }
        }

        for(int j = 0; j < n; j++)
        {
            if(reach[j] != (s[st][j] - '0'))
            {
                cout << "No\n";
                return;
            }
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
