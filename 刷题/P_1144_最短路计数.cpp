#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

struct DIJ
{
    using PII = pair<i64, i64>;
    vector<i64> dis;
    vector<int> vis;
    vector<int> ans;
    vector<vector<array<i64, 2>>> G;

    int n;
    DIJ() {}
    DIJ(int n_): n(n_) {G.resize(n + 1);}

    void add(int u, int v, int w)
    {
        G[u].push_back({v, w});
    }

    void dijkstra(int s, i64 start) //起点 s, 开始时带的权值 start
    {
        dis.assign(n + 1, 1e18);
        vis.assign(n + 1, 0);
        ans.assign(n + 1, 0);
        priority_queue<PII> pq;
        ans[s] = 1;
        dis[s] = start;
        pq.push({-dis[s], s});
        while(!pq.empty())
        {
            auto [now, u] = pq.top();
            pq.pop();
            now = -now;
            if(vis[u]) continue;
            vis[u] = 1;

            for(auto [v, w] : G[u])
            {
                auto nxt = now + w;
                if(dis[v] > nxt)
                {
                    ans[v] = ans[u];
                    dis[v] = nxt;
                    pq.push({-dis[v], v});
                }
                else if(dis[v] == nxt)
                {
                    ans[v] = (ans[v] + ans[u]) % 100003;
                }
            }
        }
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    
    DIJ D(n);
    for(int i = 1; i <= m; i++)
    {
        int u, v; cin >> u >> v;
        D.add(u, v, 1);
        D.add(v, u, 1);
    }
    D.dijkstra(1, 0);
    for(int i = 1; i <= n; i++) cout << D.ans[i] << "\n";
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    while(t--)
    {
        solve();
    }
    return 0;
}
