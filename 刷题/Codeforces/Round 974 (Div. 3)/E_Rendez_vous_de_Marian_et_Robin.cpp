#include <bits/stdc++.h>
#define int long long
using i64 = long long;
using namespace std;

const int N = 2e5 + 10;

struct node
{
    int v, w;
    bool has;
    bool operator <(const node& b) const
    {
        return w > b.w;
    }
};

vector<node> g[N];
int n, m, h;
i64 dist[N][2], has_dist[N][2]; //dist[i][0] : 无马时从1号点到i号点的距离
bool has_horse[N];              //dist[i][1] : 无马时从n号点到i号点的距离
bool vis[N][2];

void init()
{
    for(int i = 1; i <= n; i++) dist[i][0] = dist[i][1] = has_dist[i][0] = has_dist[i][1] = 1e18;
    for(int i = 1; i <= n; i++) g[i].clear(), has_horse[i] = false;
    for(int i = 1; i <= h; i++)
    {
        int x; cin >> x;
        has_horse[x] = true;
    }
    for(int i = 1; i <= m; i++)
    {
        int x, y, z;
        cin >> x >> y >> z;
        g[x].push_back({y, z, has_horse[x]});
        g[y].push_back({x, z, has_horse[y]});
    }
}

void dijkstra1(int start)
{
    for(int i = 1; i <= n; i++) vis[i][0] = vis[i][1] = false;
    dist[start][0] = 0; 
    priority_queue<node> pq;
    pq.push({start, 0, false});
    while(!pq.empty())
    {
        node now = pq.top();
        pq.pop();
        int nxt = now.v;
        bool flag = (now.has || has_horse[nxt]);
        if(vis[nxt][flag] == true) continue;
        vis[nxt][flag] = true;
        int len = g[nxt].size();
        for(int i = 0; i < len; i++)
        {
            int W = flag ? g[nxt][i].w / 2 : g[nxt][i].w;
            int V = g[nxt][i].v;
            if(dist[V][flag] > dist[nxt][now.has] + W)
            {
                dist[V][flag] = dist[nxt][now.has] + W;
                pq.push({V, dist[V][flag], flag});
            }
        } 
    }
}

void dijkstra2(int start)
{
    for(int i = 1; i <= n; i++) vis[i][0] = vis[i][1] = false;
    has_dist[start][0] = 0; 
    priority_queue<node> pq;
    pq.push({start, 0, false});
    while(!pq.empty())
    {
        node now = pq.top();
        pq.pop();
        int nxt = now.v;
        bool flag = (now.has || has_horse[nxt]);
        if(vis[nxt][flag] == true) continue;
        vis[nxt][flag] = true;
        int len = g[nxt].size();
        for(int i = 0; i < len; i++)
        {
            int W = flag ? g[nxt][i].w / 2 : g[nxt][i].w;
            int V = g[nxt][i].v;
            if(has_dist[V][flag] > has_dist[nxt][now.has] + W)
            {
                has_dist[V][flag] = has_dist[nxt][now.has] + W;
                pq.push({V, has_dist[V][flag], flag});
            }
        } 
    }
}

void solve()
{
    cin >> n >> m >> h;

    init();

    dijkstra1(1);
    dijkstra2(n);

    i64 ans = 1e18;

    for(int i = 1; i <= n; i++)
    {
        ans = min(max(min(dist[i][0], dist[i][1]), min(has_dist[i][0], has_dist[i][1])), ans);
    }
    if(ans == 1e18) cout << -1 << "\n";
    else cout << ans << "\n";
    
}
signed main()
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
/*
对于有马和无马两种情况做分类

先对无马的情况跑一遍Dij， 再对有马的情况跑一遍

然后再两种情况中取最小值，更新答案
*/