#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 2e5 + 10;
vector<int> g[N];
int mx[N], cnt[N];

void dfs(int u)
{
    mx[u] = u;
    for(auto v : g[u])
    {
        dfs(v);
        mx[u] = max(mx[u], mx[v]);
    }
}

void solve()
{
    int n;
    i64 w;
    cin >> n >> w;
    for(int i = 1; i <= n; i++) g[i].clear(), mx[i] = cnt[i] = 0;
    for(int i = 2; i <= n; i++)
    {
        int fa; cin >> fa;
        g[fa].push_back(i);
    }

    dfs(1);
    for(int i = 2; i <= n; i++) cnt[i - 1]++, cnt[mx[i]]++;
    i64 ans = n * w, now = n, sum = 0;
    for(int i = 1; i <= n - 1; i++)
    {
        i64 x, y;
        cin >> x >> y;
        cnt[x - 1]--;
        cnt[mx[x]]--;
        sum += y;
        ans -= (now - 2) * y;
        if(cnt[x - 1] == 0) ans -= (w - sum), now--;
        if(cnt[mx[x]] == 0) ans -= (w - sum), now--;
        cout << ans << " ";
    }
    cout << "\n";
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
观察发现 : 一条边只会在出现在两个组中
由于节点编号满足 dfs 序, 而 dfs 序有一些有用的性质:
对于一条边 u -> v, (u < v) 而言, 有哪些 i 点满足组 (i, i % n + 1) 经过边 u -> v
画图可得, 有且仅有 当 i = v - 1 和 i = v 子树中编号最大的节点 时构成的组才会经过边 u -> v

因此, 当给出一个点 x 时, 代表点 x 和它的父节点所连的边已经确定, 即 i = x - 1 和 i = x 子树中编号最大的节点 这两组包含这条边, 我们需要在这两组中减去这条边
我们先统计一下每一组包含了多少边, cnt[i] 为 (i, i % n + 1) 这组的边数:
    枚举 v, 从 2 到 n, 每个 v 都有两种 i
我们也要预处理一下对于一个节点 i 的子树中的最大编号, dfs 即可

由于一开始所有边都没确认, 因此 ans = n * w
每次确定一个边权 y 时, 未分配的权值都会减少 y, 所有不经过这条边且存在未确定边的路径的距离都将减少 y, 而经过这条边的路径的距离不会发生变化
假设存在未确定边权的路径数为 now, 则每确定一个y, 都有 ans -= (now - 2) * y
此外, 如果确定完之后有一些组的路径边权已经完全确定, 那它们就不能加上未分配的边权, 我们统计一下到目前为止已经确定的边权 sum, 让 ans -= (w - sum) 即可

*/ 