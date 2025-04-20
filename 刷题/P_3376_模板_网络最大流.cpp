#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

struct Dinic
{
    struct Edge
    {
        int v;
        i64 cap;
    };

    const i64 INF = 2e18;
    int n, m, s, t;
    vector<vector<int>> g;
    vector<Edge> e;
    vector<int> dis, fir;

    Dinic() {};
    Dinic(int n_, int m_, int s_, int t_)
    {
        n = n_, m = m_, s = s_, t = t_;
        g = vector<vector<int>>(n + 1);
        e.reserve(m * 2);
    }

    void add(i64 u, i64 v, i64 w)
    {
        g[u].push_back(e.size());
        e.push_back({v, w});
        g[v].push_back(e.size());
        e.push_back({u, 0});
    }

    bool bfs()
    {
        dis = fir = vector<int>(n + 1, 0);
        dis[s] = true;
        queue<int> q;
        q.push(s);
        while(!q.empty())
        {
            auto u = q.front();
            q.pop();
            for(auto nxt : g[u])
            {
                auto [v, cap] = e[nxt];
                if(dis[v] || cap <= 0) continue;
                dis[v] = dis[u] + 1;
                q.push(v);
                if(v == t) return true;
            }
        }
        return false;
    }

    i64 dfs(int u, i64 flow)
    {
        if(u == t) return flow;
        i64 res = 0;
        for(int i = fir[u]; i < g[u].size(); i++)
        {
            int id = g[u][i];
            fir[u] = i;
            auto [v, cap] = e[id];
            if(dis[v] == dis[u] + 1 && cap > 0)
            {
                i64 cur = dfs(v, min(flow, cap));
                if(cur == 0) dis[v] = 0;
                e[id].cap -= cur;
                e[id ^ 1].cap += cur;
                res += cur;
                flow -= cur;
                if(flow == 0) return res;
            }
        }
        return res;
    }

    i64 maxflow()
    {
        i64 res = 0;
        while(bfs()) res += dfs(s, INF);
        return res;
    }
};

void solve()
{
    int n, m, s, t;
    cin >> n >> m >> s >> t;

    Dinic D(n, m, s, t);
    for(int i = 1; i <= m; i++)
    {
        i64 u, v, w; cin >> u >> v >> w;
        D.add(u, v, w);
    }
    i64 ans = D.maxflow();
    cout << ans << "\n";
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
