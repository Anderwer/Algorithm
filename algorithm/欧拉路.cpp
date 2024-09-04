
欧拉路的判别法: 
    1.对于无向图G, G中存在欧拉回路当且仅当G中所有度非0的点是连通的且没有奇数度数的点
    2.对于无向图G, G中存在欧拉路当且仅当G中所有度非0的点是连通的且G中恰好有0个或2个奇数度数的点(0个表示存在欧拉回路)
    3.对于有向图G, G中存在欧拉回路当且仅当G中所有度非0的点是强连通的且每个点的入度和出度相同
    4.对于有向图G, G中存在欧拉路当且仅当:
        (a). 将G中所有有向边改为无向边后, G中所有度非0的点是连通的
        (b). 最多只有一个点的出度减去入度为1
        (c). 最多只有一个点的入度减去出度为1
        (d). 其他所有点的入度等于出度


求欧拉路的流程:
    1.先判断图中是否存在欧拉路(检查度非0的点的连通性以及度数)
    2.然后采用dfs来构造求解欧拉路,这里求得是有向图的欧拉路:
        (a).令 P 为最终的路径序列,记路径起点为x
        (b).dfs(node u):
            . 遍历所有u连出去的边u->v, 且u->v之前没有被访问过:
                .将边u->v打上标记 //如果是无向图的话这时候v->u也要打上标记
                .dfs(v);
                .将边u->添加到路径序列P中
        (c).dfs(x)结束后,将P中记录的边倒序输出,即为求得的欧拉路
    3.时间复杂度O(m)


代码实现(有向图) :

const int N = 1005; //点
const int M = 5005; //边
vector<int> g[N];
int n, m, l, num[N], din[N], dout[N], ans[M]; //num[]统计当前点走出过几条边, din[]存入度, dout[]存出度, ans[]存欧拉路径 

void dfs(int x)
{
    while(num[x] < dout[x])
    {
        int y = g[x][num[x]];
        num[x]++;
        dfs(y);
        ans[++l] = y;
    }
}

bool Euler()
{
    int x = 0, y = 0, z = 0; //x确定dfs起点, y统计出度比入度多1的点数量, z统计入度不等于出度的点数量
    for(int i = 1; i <= n; i++)
    {
        if(din[i] + 1 == dout[i]) x = i, y++;
        if(din[i] != dout[i]) z++;
    }
    if(!((y == 1 && z == 2) || !z)) return false; //不存在欧拉路
    if(x == 0)
    {
        for(int i = 1; i <= n; i++) if(din[i]) x = i;
    }
    memset(num, 0, sizeof(num));
    l = 0;
    dfs(x);
    ans[++l] = x;
    return l == m + 1;
}

void solve()
{
    cin >> n >> m;
    for(int i = 1; i <= m; i++)
    {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        dout[u]++, din[v]++;
    }
    bool flag = Euler();
    if(flag)
    {
        cout << "YES\n";
        for(int i = l; i; i--) cout << ans[i] << " ";
    }
    else cout << "NO\n";
}

代码实现(无向图):

const int N = 1005;
const int M = 5005;
struct Node{
    int y, idx;
    Node(int _y, int _idx) {y = _y; idx = _idx;};
};
vector<Node> g[N + 1];
int n, m, l, cnt, num[N], v[N], d[N], ans[M];
bool vis[2 * M];

void dfs(int x)
{
    while(num[x] < v[x])
    {
        int y = g[x][num[x]].y, idx = g[x][num[x]].idx;
        if(vis[idx] == false)
        {
            num[x]++;
            vis[idx] = vis[idx ^ 1] = true;
            dfs(y);
            ans[++l] = y;
        }
        else num[x]++;
    }
}

bool Euler()
{
    int x = 0, y = 0; //x确定dfs起点,y统计度为奇数的点数量
    for(int i = 1; i <= n; i++)
        if(d[i] & 1) x = i, y++;
    if(y && y != 2) return false; //不存在欧拉路
    if(x == 0)
    {
        for(int i = 1; i <= n; i++)
            if(d[i]) x = i;
    }
    memset(num, 0, sizeof(num));
    memset(vis, false, sizeof(vis));
    l = 0;
    dfs(x);
    ans[++l] = x;
    return l == m + 1;
}

void solve()
{
    cin >> n >> m;
    for(int i = 1; i <= m; i++)
    {
        int x, y; cin >> x >> y;
        g[x].push_back(Node(y, ++cnt));
        g[y].push_back(Node(x, ++cnt));
        d[x]++, d[y]++;
    }
    for(int i = 1; i <= n; i++) v[i] = g[i].size();
    bool flag = Euler();
    if(flag)
    {
        cout << "YES\n";
        for(int i = l; i; i--) cout << ans[i] << " ";
    }
    else cout << "NO\n";
}