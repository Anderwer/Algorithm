#include <bits/stdc++.h>
#define int long long
using i64 = long long;
using namespace std;
const int N = 2e5 + 10;
bool vis[N];
vector<int> g[N];
int f[N], d[N];

void solve()
{
    int n, m, mx = 0, max_x = 0;
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
    {
        int l; cin >> l;
        mx = max(mx, l + 4);
        for(int j = 0; j <= l + 10; j++) vis[j] = false;
        for(int j = 1; j <= l; j++)
        {
            int x; cin >> x;
            if(x <= l + 4) vis[x] = true;
        }
        int u = 0;
        while(vis[u]) u++;
        int v = u;
        vis[u] = true;
        while(vis[v]) v++;
        g[v].push_back(u); //反向建DAG, 更好dp
        d[u]++;
        max_x = max(max_x, u);
        //cout << u << " -> " << v << "\n";
    }

    for(int i = mx; i >= 0; i--) //dp
    {
        for(auto v : g[i])
        {
            if(f[v] == 0 && f[i] == 0) f[v] = i;
            else f[v] = max(f[v], f[i]);
        }
    }

    for(int i = 0; i <= mx; i++)
    {
        if(d[i] > 1) max_x = max(max_x, f[i]);
    }
    i64 ans = 0;
    
    for(int x = 0; x <= min(mx, m); x++)
    {
        ans += max({x, f[x], max_x});
    }
    if(m > mx) ans += (mx + 1 + m) * (m - mx) / 2;
    
    //for(int i = 0; i <= 3; i++) cout << f[i] << " ";
    cout << ans << "\n";    
    for(int i = 0; i <= mx + 1; i++) g[i].clear(), f[i] = d[i] = 0;
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
对于每一组, 我们统计一下这组第一个未出现的非负整数 x 和第二个未出现的非负整数 y
对于一个 k, 如果 k = x, 那我们把 k 加入到这组, 就能把 k 变成 y, 否则只能把 k 变成 x
由于每一组至多只能选一次, 我们把第 i 组得到的 x[i] 和 y[i] 进行连边, x[i] -> y[i], 最终我们会得到多个 DAG

考虑当 k != x[i] 时, 我们要把 k 变成 x[i], 则不能再把 k 变成 y[i], 因为一组只能选一次
这相当于把 k 变成 x[i] 之后, 删去 x[i] -> y[i] 这条边
因此, 如果一个 DAG 中存在一个点 x[i] 的出度 > 1, 那么可以先把 k 变成 x[i], 再删除任意一条出去的边, 因为总还有其他路径到达终点 
 
设 f[i] : 从点 i 出发能到达的最远的点
如果一个 x 在一个 DAG 中, 它可以直接到达 f[x]
如果一个 DAG 中有出度 > 1 的点, 则 x 也可以到达 f[i]
其次, 上面两种情况都不满足时, x 可以选择一个出度为 1的比它更大的点
*/