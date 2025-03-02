#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void add(int x, int y, vector<int>& f, vector<array<int, 3>>& ans)
{
    if(f[x] == y && f[y] == x)
    {
        f[x] = f[y] = -1;
        return;
    }
    else if(f[x] != -1) //有边 <x, z>, f[x] = f[z] = -1, 递归连 <y, z>
    {
        int z = f[x];
        ans.push_back({x, y, z});
        f[x] = f[z] = -1;
        add(y, z, f, ans);
    } 
    else if(f[y] != -1) //有边 <y, z>, f[y] = f[z] = -1, 递归连 <x, z>
    {
        int z = f[y];
        ans.push_back({x, y, z});
        f[y] = f[z] = -1;
        add(x, z, f, ans);
    }
    else f[x] = y, f[y] = x;
}

void solve()
{
    int n, m;
    cin >> n >> m;

    vector<int> f(n + 1, -1);
    vector<array<int, 3>> ans;

    for(int i = 1; i <= m; i++)
    {
        int u, v; cin >> u >> v;
        add(u, v, f, ans);
    }

    vector<bool> vis(n + 1, false);
    vector<array<int, 2>> edge;
    for(int i = 1; i <= n; i++)
    {
        if(f[i] == -1) continue;
        if(vis[i]) continue;
        edge.push_back({i, f[i]});
        vis[i] = vis[f[i]] = true;
    }

    if(!edge.empty())
    {
        auto [a, b] = edge[0];
        for(int i = 1; i < edge.size(); i++) ans.push_back({a, edge[i][0], edge[i][1]});
        for(int i = 1; i <= n; i++)
        {
            if(f[i] != -1) continue;
            ans.push_back({a, b, i});
            b = i;
        }
    }
    cout << ans.size() << "\n";
    for(auto [x, y, z] : ans) cout << x << ' ' << y << ' ' << z << "\n";
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

/*
题目要求把一张图变成树, 即我们可以通过操作把边数从 m 变成 n - 1 或者 变成 0
观察得, 一些情况有特殊性质

    z
   / \
  /   \    对于这种情况, 我们贪心的将 <x, y> 相连, 然后取消边 <x, z> 和 <y, z>, 这样能使 edgeNum - 1
 x     y

    z
   / \
  /   \    对于这种情况, 我们选择 V{x, y, z} 进行操作, 这样三条边都没有了   
 x- - -y

最后, 我们总能得到一些零散的边和零散的点, 先选一条零散的边 <a, b>, 然后将所有零散的边与点 a 相连, 构成菊花图
此时如果还有一些零散的点 x, 我们选择 V{a, b, x} 进行操作, 这样点 x 就插入到 <a, b> 的中间了
对于零散的点 y, 重复上述步骤, 将 y 插入到 <a, x> 中即可

对于边的存储结构, 我们 设 f[x] = y 表示 x 连的边是 y
当 add(x, y) 时, 有以下几种情况:
如果 存在 f[x] = z, 那么说明有边 <x, z>, 现在要连 <x, y>, 这样构成了第一种性质, 我们选择 V{x, y, z}, 把 f[x] = -1, 递归连 <y, z>
如果 存在 f[y] = z, 那么把 f[y] = -1, 递归连 <x, z>
特殊的, 如果递归到了 f[x] == y && f[y] == x, 说明构成了第二种性质(成环), 执行 f[x] = f[y] = -1
否则, 当 f[x] = -1 && f[y] = -1 时, 直接连边即可

*/