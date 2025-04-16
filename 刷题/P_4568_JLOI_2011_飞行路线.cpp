#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

struct DIJ
{
    using PII = array<i64, 3>;
    vector<vector<i64>> dis;
    vector<vector<int>> vis;
    vector<vector<array<i64, 2>>> G;

    int n;
    DIJ() {}
    DIJ(int n_): n(n_) {G.resize(n + 1);}

    void add(int u, int v, int w)
    {
        G[u].push_back({v, w});
    }

    void dijkstra(int s, i64 start, int k) //起点 s, 开始时带的权值 start, k 层图
    {
        dis = vector<vector<i64>>(n + 1, vector<i64>(k + 1, 2e18));
        vis = vector<vector<int>>(n + 1, vector<int>(k + 1, 0));
        priority_queue<PII> pq;
        dis[s][0] = start;
        pq.push({-dis[s][0], s, 0});
        while(!pq.empty())
        {
            auto [now, u, cnt] = pq.top();
            pq.pop();
            now = -now;
            if(vis[u][cnt]) continue;
            vis[u][cnt] = 1;

            for(auto [v, w] : G[u])
            {
                if(cnt < k && dis[v][cnt + 1] > dis[u][cnt]) //使用零代价机会
                {
                    dis[v][cnt + 1] = dis[u][cnt];
                    pq.push({-dis[v][cnt + 1], v, cnt + 1});
                }
                if(dis[v][cnt] > dis[u][cnt] + w) //不使用
                {
                    dis[v][cnt] = dis[u][cnt] + w;
                    pq.push({-dis[v][cnt], v, cnt});
                }
            }
        }
    }
};

void solve()
{
    int n, m, k, s, t;
    cin >> n >> m >> k >> s >> t;
    s++, t++;

    DIJ D(n);
    for(int i = 1; i <= m; i++)
    {
        int u, v, w; cin >> u >> v >> w;
        D.add(u + 1, v + 1, w);
        D.add(v + 1, u + 1, w);
    }
    D.dijkstra(s, 0, k);
    i64 ans = 2e18;
    for(int i = 0; i <= k; i++) ans = min(ans, D.dis[t][i]);
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
