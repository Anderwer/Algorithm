#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

struct SSP //Successive Shortest Path
{
    struct Edge
    {
        int v, next;
        i64 cap, cost;
    };

    const i64 INF = 2e18;
    int n, m, s, t;
    vector<int> head;
    vector<Edge> e;

    SSP() {};
    SSP(int n_, int m_, int s_, int t_)
    {
        n = n_, m = m_, s = s_, t = t_;
        head = vector<int>(n + 1, -1);
        e.reserve(m * 2);
    }

    void add(i64 u, i64 v, i64 cap, i64 cost)
    {
        e.push_back({v, head[u], cap, cost});
        head[u] = e.size() - 1;
        e.push_back({u, head[v], 0, -cost});
        head[v] = e.size() - 1;
    }

    pair<i64, i64> ssp()
    {
        i64 res = 0, totalCost = 0;
        vector<i64> dis(n + 1);
        vector<int> curHead(n + 1), path(n + 1), vis(n + 1);
        while(true)
        {
            dis = vector<i64>(n + 1, INF);
            vis = vector<int>(n + 1, 0);
            queue<int> q;
            q.push(s);
            dis[s] = 0, path[s] = -1;

            while(!q.empty())
            {
                auto u = q.front();
                q.pop();
                vis[u] = false;
                for(int i = head[u]; i != -1; i = e[i].next)
                {
                    auto [v, _, cap, cost] = e[i];
                    if(dis[v] > dis[u] + cost && cap > 0)
                    {
                        dis[v] = dis[u] + cost;
                        path[v] = i;
                        if(vis[v]) continue;
                        vis[v] = true;
                        q.push(v);
                    }
                }
            }
            if(dis[t] == INF) break;
            i64 minFlow = INF;
            for(int i = path[t]; i != -1; i = path[e[i ^ 1].v])
                minFlow = min(minFlow, e[i].cap);
            for(int i = path[t]; i != -1; i = path[e[i ^ 1].v])
            {
                e[i].cap -= minFlow;
                e[i ^ 1].cap += minFlow;
            }
            res += minFlow;
            totalCost += minFlow * dis[t];
        }
        return {res, totalCost};
    }
};

void solve()
{
    int n, m, s, t;
    cin >> n >> m >> s >> t;

    SSP S(n, m, s, t);
    for(int i = 1; i <= m; i++)
    {
        i64 u, v, cap, cost; cin >> u >> v >> cap >> cost;
        S.add(u, v, cap, cost);
    }
    auto [flow, cost] = S.ssp();
    cout << flow << " " << cost << "\n";
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
