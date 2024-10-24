#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 5e5 + 10;

vector<int> g[N];
int deep[N], son_deep[N];
int max_deep;

int dfs(int u, int fa, int dep)
{
    max_deep = max(max_deep, dep);
    deep[dep]++;
    
    int son_mx_deep = dep;
    for(auto v : g[u])
    {
        if(v == fa) continue;
        son_mx_deep = max(son_mx_deep, dfs(v, u, dep + 1));
    }
    son_deep[son_mx_deep]++;
    return son_mx_deep;
}

void solve()
{
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        g[i].clear();
        deep[i] = son_deep[i] = 0;
    }
    for(int i = 1; i <= n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    max_deep = 0;
    dfs(1, 0, 1);

    for(int i = 1; i <= max_deep; i++)
    {
        deep[i] += deep[i - 1];
        son_deep[i] += son_deep[i - 1];
    }

    int ans = 1e9;
    for(int i = 1; i <= max_deep; i++)
    {
        int res = deep[max_deep] - deep[i] + son_deep[i - 1];
        ans = min(ans, res);
    }
    cout << ans << "\n";
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
先dfs一遍记录一下所有叶子节点离根节点的距离

假设一棵树的最深深度是max_deep
思路 : 最终的树要变成统一深度, 则可以从 1 到 max_deep 遍历深度, 看哪个深度操作次数最少

而要把一棵树变成相同深度 deep, 需要注意:
    所有比 deep 深的节点都应删到和 deep 一样深
    所有比 deep 浅的叶子节点都应完全删去
    
通过分析, 我们需要一个 树上深度前缀和 快速算出比 deep 深的节点个数
我们还需要一个以深度最深的作为主干, 以深度为下标的数组记录不同深度的子节点数量, 具体见代码实现
同样, 这个数组也可以用前缀和 快速算出比 deep 浅的子节点数量

最终 ans = min(ans, deep[max_deep] - deep[i] + son_deep[i - 1])
*/
