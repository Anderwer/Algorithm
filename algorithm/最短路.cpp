#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

// 最短路模板集合
// 包含:
// 1. Dijkstra(堆优化, 非负权单源最短路)
// 2. BellmanFord(可处理负边, 单源最短路)
// 3. SPFA(可处理负边, 可判负环)
// 4. Floyd(全源最短路)
//
// 约定:
// - 点编号默认为 1..n
// - 若为有向图, add(u, v, w)
// - 若为无向图, 自行 add(u, v, w), add(v, u, w)

struct Dijkstra
{
    static constexpr i64 INF = (i64)4e18;
    using PII = pair<i64, int>;

    int n;
    vector<vector<array<i64, 2>>> g;
    vector<i64> dis;
    vector<int> vis;

    Dijkstra() {}
    Dijkstra(int n_)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        g.assign(n + 1, {});
    }

    void add(int u, int v, i64 w)
    {
        g[u].push_back({v, w});
    }

    void work(int s)
    {
        dis.assign(n + 1, INF);
        vis.assign(n + 1, 0);

        priority_queue<PII, vector<PII>, greater<PII>> pq;
        dis[s] = 0;
        pq.push({0, s});

        while(!pq.empty())
        {
            auto [d, u] = pq.top();
            pq.pop();
            if(vis[u]) continue;
            vis[u] = 1;

            for(auto [v, w] : g[u])
            {
                if(dis[v] > d + w)
                {
                    dis[v] = d + w;
                    pq.push({dis[v], v});
                }
            }
        }
    }
};

struct BellmanFord
{
    static constexpr i64 INF = (i64)4e18;

    struct Edge
    {
        int u, v;
        i64 w;
    };

    int n;
    vector<Edge> e;
    vector<i64> dis;

    BellmanFord() {}
    BellmanFord(int n_)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        e.clear();
    }

    void add(int u, int v, i64 w)
    {
        e.push_back({u, v, w});
    }

    // 返回是否存在从源点可达的负环
    bool work(int s)
    {
        dis.assign(n + 1, INF);
        dis[s] = 0;

        for(int i = 1; i <= n - 1; i++)
        {
            bool ok = false;
            for(auto [u, v, w] : e)
            {
                if(dis[u] == INF) continue;
                if(dis[v] > dis[u] + w)
                {
                    dis[v] = dis[u] + w;
                    ok = true;
                }
            }
            if(!ok) break;
        }

        for(auto [u, v, w] : e)
        {
            if(dis[u] == INF) continue;
            if(dis[v] > dis[u] + w) return true;
        }
        return false;
    }
};

struct SPFA
{
    static constexpr i64 INF = (i64)4e18;

    int n;
    vector<vector<array<i64, 2>>> g;
    vector<i64> dis;
    vector<int> vis, cnt;

    SPFA() {}
    SPFA(int n_)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        g.assign(n + 1, {});
    }

    void add(int u, int v, i64 w)
    {
        g[u].push_back({v, w});
    }

    // 单源最短路, 返回是否存在从源点可达的负环
    bool work(int s)
    {
        dis.assign(n + 1, INF);
        vis.assign(n + 1, 0);
        cnt.assign(n + 1, 0);

        queue<int> q;
        dis[s] = 0;
        vis[s] = 1;
        q.push(s);

        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            vis[u] = 0;

            for(auto [v, w] : g[u])
            {
                if(dis[u] == INF) continue;
                if(dis[v] > dis[u] + w)
                {
                    dis[v] = dis[u] + w;
                    cnt[v] = cnt[u] + 1;
                    if(cnt[v] >= n) return true;
                    if(!vis[v])
                    {
                        vis[v] = 1;
                        q.push(v);
                    }
                }
            }
        }
        return false;
    }

    // 判整张图是否存在负环
    // 做法: 建立超级源 0, 向每个点连权值 0 的边
    bool hasNegCycle()
    {
        dis.assign(n + 1, 0);
        vis.assign(n + 1, 1);
        cnt.assign(n + 1, 0);

        queue<int> q;
        for(int i = 1; i <= n; i++) q.push(i);

        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            vis[u] = 0;

            for(auto [v, w] : g[u])
            {
                if(dis[v] > dis[u] + w)
                {
                    dis[v] = dis[u] + w;
                    cnt[v] = cnt[u] + 1;
                    if(cnt[v] >= n) return true;
                    if(!vis[v])
                    {
                        vis[v] = 1;
                        q.push(v);
                    }
                }
            }
        }
        return false;
    }
};

struct Floyd
{
    static constexpr i64 INF = (i64)4e18;

    int n;
    vector<vector<i64>> dis;

    Floyd() {}
    Floyd(int n_)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        dis.assign(n + 1, vector<i64>(n + 1, INF));
        for(int i = 1; i <= n; i++) dis[i][i] = 0;
    }

    void add(int u, int v, i64 w)
    {
        dis[u][v] = min(dis[u][v], w);
    }

    void work()
    {
        for(int k = 1; k <= n; k++)
        {
            for(int i = 1; i <= n; i++)
            {
                if(dis[i][k] == INF) continue;
                for(int j = 1; j <= n; j++)
                {
                    if(dis[k][j] == INF) continue;
                    if(dis[i][j] > dis[i][k] + dis[k][j])
                    {
                        dis[i][j] = dis[i][k] + dis[k][j];
                    }
                }
            }
        }
    }
};

/*
使用示例:

1. Dijkstra
Dijkstra dij(n);
dij.add(u, v, w);
dij.work(s);
auto dist = dij.dis[t];

2. BellmanFord
BellmanFord bf(n);
bf.add(u, v, w);
bool hasNeg = bf.work(s);

3. SPFA
SPFA spfa(n);
spfa.add(u, v, w);
bool hasNeg = spfa.work(s);      // 判从 s 可达的负环
bool anyNeg = spfa.hasNegCycle(); // 判整图负环

4. Floyd
Floyd floyd(n);
floyd.add(u, v, w);
floyd.work();
auto dist = floyd.dis[u][v];
*/