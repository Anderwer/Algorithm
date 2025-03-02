#include <bits/stdc++.h>
----------------------------------------------------------------------------------------
SPFA : 用于负环

const int maxn = 5e5 + 10;

vector<pair<int,int>> g[maxn]; //有向图,g[u].first是v,g[u].second是w
int dist[maxn], cnt[maxn], vis[maxn];
queue<int> q;

bool spfa(int s, int n) //s是起点,n是n个点, 最终最短路距离dist[x]表示从s到x的最短距离
{
    memset(dist, 127, (n + 1) * sizeof(int));
    dist[s] = 0, vis[s] = 1;
    q.push(s);
    while(!q.empty())
    {
        int u = q.front();
        q.pop(), vis[u] = 0;
        for(auto ed : g[u])
        {
            int v = ed.first, w = ed.second;
            if(dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                cnt[v] = cnt[u] + 1;
                if(cnt[v] >= n) return false;
                if(!vis[v]) q.push(v), vis[v] = 1;
            }
        }
    }
    return true;
}

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
    DIJ(int n_): n(n_) {G.resize(n + 1);}

    void add(int u, int v, int w)
    {
        G[u].push_back({v, w});
    }

    void dijkstra(int s, i64 start) //起点 s, 开始时带的权值 start
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



