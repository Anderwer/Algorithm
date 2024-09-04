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

const int N = 500005;

struct node
{
    int v;//指向下一个点
    int w;//边权
    bool operator < (const node &b)const//重载 < 
    {
        return w > b.w;
    }
}now,tmp;
int n,m,s;
vector<node> MAP[N];//图
int d[N];//最短路数组
bool vis[N];//标记数组
void dijkstra(int s,int e)//从s到e
{
    d[s] = 0;
    now.v = s;
    now.w = 0;
    priority_queue<node> q;
    q.push(now);
    while(!q.empty())//BFS
    {
        now = q.top();
        q.pop();
        if(vis[now.v] == true) continue;
        vis[now.v] = true;
        int len = MAP[now.v].size();
        for(int i = 0; i < len; i++)//遍历一个点所连的后面几个点
        {
            tmp = MAP[now.v][i];
            if(d[now.v] + tmp.w < d[tmp.v])
            {
                d[tmp.v] = d[now.v] + tmp.w;
                q.push((node){ tmp.v, d[tmp.v]});
            }
        }
    }
}

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



