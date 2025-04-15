#include <bits/stdc++.h>
----------------------------------------------------------------------------------------
SPFA : 判断负环, 负权图单源最短路O(nm)

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

---------------------------------------------------------------------------------------------
差分约束问题: SPFA求解O(nm)

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
    }

    bool spfa()
    {
        queue<int> q;
        dis[0] = 0;
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
                if(dis[v] > dis[u] + w)
                {
                    dis[v] = dis[u] + w;
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
};

---------------------------------------------------------------------------------------------
Dijkstra : 单源最短路O(n^2)

struct DIJ
{
    const i64 INF = 2e18;
    using PII = pair<i64, i64>;
    vector<i64> dis;
    vector<int> vis;
    vector<vector<array<i64, 2>>> G;

    int n;
    DIJ() {}
    DIJ(int n_)
    {
        n = n_;
        G = vector<vector<array<i64, 2>>>(n + 1);
    }

    void add(int u, int v, int w)
    {
        G[u].push_back({v, w});
    }

    void dijkstra(int s, i64 start) //起点 s, 开始时带的权值 start
    {
        dis = vector<i64>(n + 1, INF);
        vis = vector<int>(n + 1, 0);
        dis[s] = start;
        
        for(int i = 1; i <= n; i++)
        {
            i64 u = 0, mind = INF;
            for(int j = 1; j <= n; j++)
                if(vis[j] == false && dis[j] < mind) u = j, mind = dis[j];
            vis[u] = true;
            for(auto [v, w] : G[u])
                if(dis[v] > dis[u] + w) dis[v] = dis[u] + w;
        }
    }
};

---------------------------------------------------------------------------------------------
Dijkstra : 单源最短路O(mlogm)

struct DIJ
{
    using PII = pair<i64, i64>;
    vector<i64> dis;
    vector<int> vis;
    vector<vector<array<i64, 2>>> G;

    int n;
    DIJ() {}
    DIJ(int n_)
    {
        n = n_;
        G = vector<vector<array<i64, 2>>>(n + 1);
    }

    void add(int u, int v, int w)
    {
        G[u].push_back({v, w});
    }

    void dijkstra(int s, i64 start) //起点 s, 开始时带的权值 start
    {
        dis = vector<i64>(n + 1, 2e18);
        vis = vector<int>(n + 1, 0);
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
};

----------------------------------------------------------------------------------------
Floyd : 全源最短路,使用邻接矩阵O(n3)

struct Floyd
{
    const int INF = (1 << 31) - 1;
    int n;
    vector<vector<int>> f;

    Floyd() {};
    Floyd(int n_)
    {
        n = n_;
        f = vector<vector<int>>(n + 1, vector<int>(n + 1, INF));
    }

    void add(int u, int v, int w)
    {
        f[u][v] = w;
    }

    void init()
    {
        for(int i = 1; i <= n; i++) add(i, i, 0);
    }

    vector<vector<int>> floyd()
    {
        init();
        for(int k = 1; k <= n; k++)
            for(int i = 1; i <= n; i++)
                for(int j = 1; j <= n; j++)
                    if(f[i][k] < INF && f[k][j] < INF)
                        f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
        return f;
    }
};

-----------------------------------------------------------------------------------------------------------------
Johnson: 全源最短路, 可处理负边权 O(nmlogm)

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
        if(spfa() == true) // alldis[0][0] = true 说明图有负环, 不存在最短路
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
