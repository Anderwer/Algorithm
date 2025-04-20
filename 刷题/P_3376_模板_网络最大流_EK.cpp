#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

struct EK
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
    vector<int> vis, pre;
    vector<i64> flow;

    EK() {};
    EK(int n_, int m_, int s_, int t_)
    {
        n = n_, m = m_, s = s_, t = t_;
        g = vector<vector<int>>(n + 1);
        e.reserve(m * 2);
        pre = vector<int>(n + 1, 0);
        flow = vector<i64>(n + 1, 0);
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
        vis = vector<int>(n + 1, 0);
        queue<int> q;
        vis[s] = true;
        q.push(s);
        flow[s] = INF;
        while(!q.empty())
        {
            auto u = q.front();
            q.pop();
            for(auto nxt : g[u])
            {
                auto [v, cap] = e[nxt];
                if(vis[v] || cap <= 0) continue;
                vis[v] = true;
                flow[v] = min(flow[u], cap);
                pre[v] = nxt;
                if(v == t) return true;
                q.push(v);
            }
        }
        return false;
    }

    i64 maxflow()
    {
        i64 res = 0;
        while(bfs())
        {
            res += flow[t];
            for(int i = t; i != s; i = e[pre[i] ^ 1].v)
            {
                e[pre[i]].cap -= flow[t];
                e[pre[i] ^ 1].cap += flow[t];
            }
        }
        return res;
    }
};

void solve()
{
    int n, m, s, t;
    cin >> n >> m >> s >> t;

    EK E(n, m, s, t);
    for(int i = 1; i <= m; i++)
    {
        i64 u, v, w; cin >> u >> v >> w;
        E.add(u, v, w);
    }
    i64 ans = E.maxflow();
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
