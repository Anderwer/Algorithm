#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

struct SPFA
{
    vector<i64> dis;
    vector<int> cnt;
    vector<int> vis;
    vector<vector<array<i64, 2>>> G;

    int n;
    SPFA() {};
    SPFA(int n_)
    {
        n = n_;
        G = vector<vector<array<i64, 2>>>(n + 1);
        dis = vector<i64>(n + 1, 2e18);
        cnt = vector<int>(n + 1, 0);
        vis = vector<int>(n + 1, 0);
    }

    void add(int u, int v, int w)
    {
        G[u].push_back({v, w});
        if(w >= 0) G[v].push_back({u, w});
    }

    bool spfa(int s)
    {
        queue<int> q;
        dis[s] = cnt[s] = 0;
        q.push(s);
        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            vis[u] = 0;
            for(auto [v, w] : G[u])
            {
                if(dis[v] > dis[u] + w)
                {
                    dis[v] = dis[u] + w;
                    cnt[v] = cnt[u] + 1;
                    if(cnt[v] >= n)
                        return true;
                    if(vis[v] == false)
                        q.push(v), vis[v] = 1;
                }
            }
        }
        return false;
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;

    SPFA S(n);
    for(int i = 1; i <= m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        S.add(u, v, w);
    }
    if(S.spfa(1)) cout << "YES\n";
    else cout << "NO\n";
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
