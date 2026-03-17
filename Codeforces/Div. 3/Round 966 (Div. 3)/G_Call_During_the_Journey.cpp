#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

struct DIJ
{
    using PII = pair<i64, i64>;
    vector<i64> dis;
    vector<vector<array<i64, 3>>> G;

    int n;
    DIJ() {}
    DIJ(int n_): n(n_) {G.resize(n + 1);}

    void add(int u, int v, int l1, int l2)
    {
        G[u].push_back({v, l1, l2});
    }

    void dijkstra(int s, i64 t_start, i64 t1, i64 t2)  
    {
        dis.assign(n + 1, 1e18);
        priority_queue<PII> pq;
        dis[s] = t_start;
        pq.push({-dis[s], s});
        while(!pq.empty())
        {
            auto [t, u] = pq.top(); //当前时间
            pq.pop();
            t = -t;
            if(dis[u] < t) continue;
            
            for(auto [v, l1, l2] : G[u])
            {
                auto now = t + l2;//先走路
                if(max(t, t1) < min(t + l1, t2)) now = min(now, t2 + l1); //判断坐车这段时间是否会打电话, 打电话的话可以选择边走路边打电话或者原地打完电话再坐车
                else now = min(now, t + l1); //如果不打电话则坐车

                if(dis[v] > now)
                {
                    dis[v] = now;
                    pq.push({-dis[v], v});
                }
            }
        }
    }
};

void solve()
{
    int n, m, t0, t1, t2;
    cin >> n >> m >> t0 >> t1 >> t2;
    DIJ dij(n);

    for(int i = 1; i <= m; i++)
    {
        int u, v, l1, l2;
        cin >> u >> v >> l1 >> l2;
        dij.add(u, v, l1, l2);
        dij.add(v, u, l1, l2);
    }
    i64 l = 0, r = t0, ans = -1;
    while(l <= r)
    {
        i64 mid = (l + r) / 2;
        dij.dijkstra(1, mid, t1, t2);
        if(dij.dis[n] <= t0) ans = mid, l = mid + 1;
        else r = mid - 1;
    }

    cout << ans << "\n";
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
