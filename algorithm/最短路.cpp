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
Dijkstra : 单源最短路O((n + m)logn)

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
        dis = vector<i64>(n + 1, 2e18);
        vis = vector<int>(n + 1, 0);
    }

    void add(int u, int v, int w)
    {
        G[u].push_back({v, w});
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
                if(dis[v] > now)
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

const int N = 1005;
int f[N][N];

void folyd(int n)
{
    for(int k = 1; k <= n; k++)
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                if(f[i][k] < (1 << 30) && f[k][j] < (1 << 30)) 
                    f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
}

void solve()
{
    int n,m,k; //n个点,m条边,k次询问
    cin >> n >> m >> k;
    memset(f, 127, sizeof(f));
    for(int i = 1; i <= m; i++)
    {
        int u,v,w;
        cin >> u >> v >> w;
        f[u][v] = w;
    }
    folyd(n);
}



