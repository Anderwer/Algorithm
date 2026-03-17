#include <bits/stdc++.h>
#define int long long
using i64 = long long;
using namespace std;
const int mod = 998244353;

int qpow(int a, int b)
{
    int res = 1;
    while(b)
    {
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

void dfs1(int u, vector<vector<int>>& g, vector<int>& fa, vector<int>& d, vector<int>& nxt)
{
    if(g[u].size() == 1 && u != 1)
    {
        d[u] = 0;
        nxt[u] = u;
        return;
    }
    for(auto v : g[u])
    {
        if(v == fa[u]) continue;
        fa[v] = u;
        dfs1(v, g, fa, d, nxt);
        d[u] = min(d[u], d[v] + 1);
    }
    int mn = 1E9 + 10;
    for(auto v : g[u])
    {
        if(v == fa[u]) continue;
        if(d[v] < mn)
        {
            mn = d[v];
            nxt[u] = v;
        }
    }
}

void dfs2(int u, vector<vector<int>>& g, vector<int>& nxt, vector<int>& fa, vector<int>& p, const int inv)
{
    if(g[u].size() == 1 && u != 1) return;
    for(auto v : g[u])
    {
        if(v == fa[u]) continue;
        dfs2(v, g, nxt, fa, p, inv);
        p[u] = qpow((2 - p[nxt[u]] + mod) % mod, mod - 2);
    }
}

void dfs3(int u, vector<vector<int>>& g, vector<int>& fa, vector<int>& p, vector<int>& ans, vector<int>& d)
{
    for(auto v : g[u])
    {
        if(v == fa[u]) continue;
        if(d[v] == 0) ans[v] = 0;
        else ans[v] = ans[u] * p[v] % mod;
        dfs3(v, g, fa, p, ans, d);
    }
}

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> g(n + 1);
    for(int i = 1; i < n; i++)
    {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> fa(n + 1, 0); //记录节点 u 的父亲
    vector<int> d(n + 1, 1E9); //统计每个节点离叶子的最近距离
    vector<int> nxt(n + 1); //记录一下节点 u 往下走是哪个儿子
    dfs1(1, g, fa, d, nxt);
    
    vector<int> p(n + 1, 0); //记录 p[u] 和 p[fa[u]] 之间的系数
    dfs2(1, g, nxt, fa, p, qpow(2, mod - 2));
    p[1] = 1;
    
    vector<int> ans(n + 1, 0);
    ans[1] = 1;
    dfs3(1, g, fa, p, ans, d);
    for(int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << "\n";
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
研究策略, 根据贪心可以知道
如果当前是 Alice 选择, 那么她必定往上走, 如果当前是 queen 选择, 那么她会往离叶子更近的那个儿子走
首先有, p[root] = 1, p[leaf] = 0
我们从其中一个叶子往上推:
p[leaf] = 0
当 u 是 leaf 的父亲时, p[u] = 0.5 * p[leaf] + 0.5 * p[u_fa] = 0.5 * p[u_fa]
当考虑 u_fa 时, p[u_fa] = 0.5 * p[u] + 0.5 * p[u_fa_fa], 则 p[u_fa] - 0.5 * p[u] = 0.5 * p[u_fa_fa], 而 p[u] 又跟 p[u_fa] 有关, 可以化简
p[u] = 0.5 * p[nxt[u]] + 0.5 * p[fa[u]]

因此发现, 节点 u 的当前概率只与它的下面一个和上面一个有关, 我们从下往上推, 这样下面就知道了, 只剩上面不知道了, 我们从下往上推的时候记录一下 p[u] = k * p[u_fa] 的系数 k
当所有系数确定完后, 由于 p[root] = 1, 我们再从上往下推回去即可

在计算前, 我们先处理一下每个节点往下走时会走哪
*/