#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 2010;
vector<int> g[N];
int n, k;

int dfs(int u, int bro, int fa, int depth)
{
    int cnt = 0;
    if(depth > k) cnt++;
    for(auto v : g[u])
    {
        if(v == fa) continue;
        cnt += dfs(v, bro, u, depth + (v != bro)); //如果 当前节点是 另一个重心, 则它的高度也不应该增加
    }
    return cnt;
}

void solve()
{
    cin >> n >> k;
    for(int i = 1; i <= n - 1; i++)
    {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int ans = 1e9;
    if(k & 1)
    {
        k /= 2;
        for(int i = 1; i <= n; i++)
        {
            for(auto j : g[i]) ans = min(ans, dfs(i, j, -1, 0));
        }
    }
    else
    {
        k /= 2;
        for(int i = 1; i <= n; i++) ans = min(ans, dfs(i, -1, -1, 0));
    }
    cout << ans << "\n";
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
/*
由于 n <= 2000, 我们可以暴力枚举每一个节点作为重心时删除的点数, 取最小值
因为直径总是经过重心

如果直径长度 k 是偶数, 那么重心只有一个, 如果一个点离重心的距离 > k / 2, 则它应该被删除

如果直径长度 k 是奇数, 那么存在两个重心, 我们两个重心连成一条边, 如果一个点离这条边的距离 > k / 2, 则它应该被删除
具体实现方法: 选一个点 i 作为其中一个重心, 枚举 i 的子节点 j , 在 dfs 中标记 i 和 j 的高度相同且都为 0, 再进行 dfs

*/