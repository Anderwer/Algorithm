1. 树的直径 : 树上任意两个节点之间最长的路径

2. 树的直径的中间节点被称为树的中心,如果直径上有偶数个节点,那么中间的两个节点都可以是树的中心.树的中心到其他点的最长距离最短.

3. 树的直径可以用两次搜索求得.第一次从任意一个节点开始搜索,找出距离最远的节点a,第二次从a节点开始搜索,找出距离节点a最远的节点b,则路径a->b即为树的直径

4. 树的中心是被唯一确定的,无论树的直径有多少条

5. 树的重心 : 对于一棵无根树,当一个节点被选为根节点,它底下的每个子节点的子树的大小最大值最小的那个节点,被称为树的重心(一棵树可能有1个或者2个重心)

6. 树的重心有一下性质
    1.当重心为根节点时,它底下的每个子树大小不大于整棵树大小的一半
    2. 重心刀其他所有节点的距离和最小

求树的重心例题 : POJ 1655

#include<iostream>
#include<vector>
#include<algorithm>
using i64 = long long;
using namespace std;
const int N = 20005;

int n,mx,ans;
vector<int> g[N];
int sz[N], dp[N]; //sz[]记录树的大小,dp[]用来实时更新树的重心大小
void dfs(int u,int fa)
{
    sz[u] = 1;
    for(auto v : g[u])
    {
        if(v == fa) continue;
        dfs(v,u);
        sz[u] += sz[v];
        dp[u] = max(dp[u], sz[v]);
    }
    dp[u] = max(dp[u], n - sz[u]);
    if(dp[u] < mx)
    {
        ans = u;
        mx = dp[u];
    }
    else if(dp[u] == mx)
    {
        ans = min(ans, u);
    }
}
void solve()
{
    cin >> n;
    mx = 1 << 30;
    ans = 0;
    for(int i = 1; i <= n; i++)
    {
        g[i].clear();
        sz[i] = 0;
        dp[i] = 0;
    }
    for(int i = 1; i <= n - 1; i++)
    {
        int u,v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1,0);
    cout << ans << " " << mx << "\n";
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


7. 利用倍增求树上LCA

思路 : 预处理出每个节点的深度和father[i][j]数组, 其中father[i][j] 指的是 节点i 往上跳2 ^ j步是哪个节点
#include<bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 500010;
vector<int> g[N];
int depth[N], father[N][21];

void dfs(int u, int fa)
{
    for(auto v : g[u])
    {
        if(v == fa) continue;
        depth[v] = depth[u] + 1;
        father[v][0] = u; //当前节点v的父亲是u
        dfs(v,u);
    }
}

int query(int x, int y) //保证x的深度更大
{
    if(depth[x] < depth[y]) swap(x,y);
    int z = depth[x] - depth[y]; //x 和 y 相差高度为z,枚举z的二进制位,遇到1就往上跳
    for(int i = 0; i <= 20 && z != 0; i++)
    {
        if(z & 1) x = father[x][i];
        z >>= 1;
    }
    if(x == y) return x; 
    for(int i = 20; i >= 0; i--) //一直往上跳,直到跳到LCA下方
    {
        if(father[x][i] != father[y][i]) x = father[x][i], y = father[y][i];
    }
    return father[x][0];
}
void solve()
{
	int n,m,s;
    cin >> n >> m >> s;
    for(int i = 1; i <= n - 1; i++)
    {
        int u,v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    depth[s] = 1;
    dfs(s,0);
    for(int i = 1; i <= 20; i++)
        for(int j = 1; j <= n; j++)
            if(father[j][i - 1]) father[j][i] = father[father[j][i - 1]][i - 1];
    for(int i = 1; i <= m; i++)
    {
        int x, y;
        cin >> x >> y;
        cout << query(x,y) << "\n";
    }
}
int main()
{
	std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
	int t = 1;
	//cin >> t;
	while(t--){
		solve();
	}
	return 0;
}