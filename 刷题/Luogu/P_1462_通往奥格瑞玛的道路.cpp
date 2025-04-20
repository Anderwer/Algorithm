#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

struct DIJ
{
    using PII = pair<i64, i64>;
    vector<i64> dis;
    vector<int> f;
    vector<int> vis;
    vector<vector<array<i64, 2>>> G;

    int n;
    DIJ() {}
    DIJ(int n_): n(n_) 
    {
        G.resize(n + 1);
        f = vector<int>(n + 1);
    }

    void add(int u, int v, int w)
    {
        G[u].push_back({v, w});
    }

    void dijkstra(int s, i64 start, int x) //起点 s, 开始时带的权值 start
    {
        dis.assign(n + 1, 1e18);
        vis.assign(n + 1, 0);
        priority_queue<PII> pq;
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
                if(dis[v] > nxt && f[v] <= x)
                {
                    dis[v] = nxt;
                    pq.push({-dis[v], v});
                }
            }
        }
    }
};

int n, m, b;
bool check(int x, DIJ& D)
{
    D.dijkstra(1, 0, x);
    return D.dis[n] <= b;
}

void solve()
{
    cin >> n >> m >> b;

    DIJ D(n);
    for(int i = 1; i <= n; i++) cin >> D.f[i];
    for(int i = 1; i <= m; i++)
    {
        int u, v, w; cin >> u >> v >> w;
        D.add(u, v, w);
        D.add(v, u, w);
    }

    i64 L = D.f[1], R = 1e9, ans = -1;
    while(L <= R)
    {
        i64 mid = (L + R) / 2;
        if(check(mid, D)) R = mid - 1, ans = mid;
        else L = mid + 1;
    }
    if(ans == -1) cout << "AFK\n";
    else cout << ans << "\n";
}

// 题目要求在他能活着从 1 到 n 的前提下, 经过城市花费的最大值最小
// 考虑二分答案, 在 check 里跑 Dijkstra 并在松弛操作中添加限制 

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
