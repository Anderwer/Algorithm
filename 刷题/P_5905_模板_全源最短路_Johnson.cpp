#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

struct Johnson
{
    using PII = pair<i64, i64>;
    vector<i64> dis;
    vector<i64> h;
    vector<int> cnt;
    vector<int> vis;
    vector<vector<array<i64, 2>>> G;

    int n;
    Johnson() {}
    Johnson(int n_)
    {
        n = n_;
        G = vector<vector<array<i64, 2>>>(n + 1);
        dis = vector<i64>(n + 1, 1e9);
        h = vector<i64>(n + 1, 1e9);
        cnt = vector<int>(n + 1, 0);
        vis = vector<int>(n + 1, 0);
    }

    void add(int u, int v, int w)
    {
        G[u].push_back({v, w});
    }

    bool spfa()
    {
        queue<int> q;
        h[0] = 0;
        vis[0] = 1;
        q.push(0);
        for(int i = 1; i <= n; i++) add(0, i, 0);
        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            vis[u] = 0;
            for(auto [v, w] : G[u])
            {
                if(h[v] > h[u] + w)
                {
                    h[v] = h[u] + w;
                    cnt[v] = cnt[u] + 1;
                    if(cnt[v] > n)
                        return true;
                    if(vis[v] == false)
                        q.push(v), vis[v] = 1;
                }
            }
        }
        return false;
    }

    void dijkstra(int s, i64 start) //起点 s, 开始时带的权值 start
    {
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
                if(dis[v] > nxt)
                {
                    dis[v] = nxt;
                    pq.push({-dis[v], v});
                }
            }
        }
    }

    vector<vector<i64>> johnson()
    {
        vector<vector<i64>> alldis(n + 1, vector<i64>(n + 1, 0));
        if(spfa() == true)
        {
            alldis[0][0] = true;
            return alldis;
        } 
        for(int u = 1; u <= n; u++)
            for(auto& [v, w] : G[u])
                w = w + h[u] - h[v];

        for(int i = 1; i <= n; i++) // 枚举起点
        {
            vis = vector<int>(n + 1, 0);
            dis = vector<i64>(n + 1, 1e9); //重置 dis
            dijkstra(i, 0);
            alldis[i] = dis;
        }
        return alldis;
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;

    Johnson J(n);
    for(int i = 1; i <= m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        J.add(u, v, w);
    }
    vector<vector<i64>> dis = J.johnson();
    if(dis[0][0] == true) cout << -1 << "\n";
    else
    {
        for(i64 i = 1; i <= n; i++)
        {
            i64 ans = 0;
            for(i64 j = 1; j <= n; j++)
            {
                if(dis[i][j] == 1e9) ans += j * dis[i][j];
                else ans += j * (dis[i][j] + J.h[j] - J.h[i]);
            }
            cout << ans << "\n";
        } 
    }
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
