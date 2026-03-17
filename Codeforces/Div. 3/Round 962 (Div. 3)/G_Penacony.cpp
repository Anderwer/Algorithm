#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

template<class Node> //区间加 + 区间查询 + 单点加 + 单点查询
struct SegmentTree
{
    #define lc u << 1
    #define rc u << 1 | 1
    const int n, M;
    vector<Node> tree;

    SegmentTree(): n(0) {}
    SegmentTree(int n_): n(n_), M(n * 4 + 10)
    {
        tree.reserve(M);
        tree.resize(M);
        build(1, 1, n);
    }

    void build(int u, i64 l, i64 r)
    {
        tree[u] = {l, r, 0, r - l + 1, 0};
        if(l == r) return;
        int mid = (l + r) >> 1;
        build(lc, l, mid);
        build(rc, mid + 1, r);
    }

    void pushup(Node& U, Node& L, Node& R)
    {
        U.Min = min(L.Min, R.Min);
        U.Sum = 0;
        if(L.Min == U.Min) U.Sum += L.Sum;
        if(R.Min == U.Min) U.Sum += R.Sum;
    }

    void init_lazy(Node& U) 
    {
        U.add = 0;
    }

    void cal_lazy(Node& Fa, Node& Son)
    {
        Son.Min += Fa.add;
    }

    void lazy_union(Node& Fa, Node& Son)
    {
        Son.add += Fa.add;
    }

    void pushdown(int u)
    {
        if(tree[u].add == 0) return;
        cal_lazy(tree[u], tree[lc]);
        cal_lazy(tree[u], tree[rc]);
        lazy_union(tree[u], tree[lc]);
        lazy_union(tree[u], tree[rc]);
        init_lazy(tree[u]);
    }

    void range_modify(int u, int l, int r, int x) //区间修改
    {
        if(l > r) return;
        if(l <= tree[u].l && r >= tree[u].r)
        {
            tree[u].Min += x; //区间修改, 区间最小值也更改了
            tree[u].add += x;
            return;
        }
        pushdown(u);
        int mid = (tree[u].l + tree[u].r) >> 1;
        if(l <= mid) range_modify(lc, l, r, x);
        if(r > mid) range_modify(rc, l, r, x);
        pushup(tree[u], tree[lc], tree[rc]);
    }
    
};

struct Node
{
    i64 l, r;
    i64 add, Sum, Min; //add 懒标记, Sum 统计最小值的数量, Min 统计最小值是什么, 如果 tree[u].Min == 0, 则 Sum 统计的是区间中 0 的数量
};


void solve()
{
    i64 n, m;
    cin >> n >> m;
    vector<vector<int>> l(n + 1), r(n + 1);
    SegmentTree<Node> ST(n);
    for(int i = 1; i <= m; i++)
    {
        int u, v; cin >> u >> v;
        l[u].push_back(v);
        r[v].push_back(u);
        ST.range_modify(1, u, v - 1, 1); //先给所有关系 +1
    }

    i64 ans = n;
    for(int i = 1; i <= n; i++) //枚举不维护的第 i 条边
    {
        for(auto v : l[i]) //左端点在 i, 右端点在 v, 不能往 i + 1 走, 要走 n -> 1 那条线, [i, v) -= 1, [1, i) U [v, n] += 1
        {
            ST.range_modify(1, i, v - 1, -1);
            ST.range_modify(1, 1, i - 1, 1);
            ST.range_modify(1, v, n, 1);
        }
        for(auto v : r[i]) //右端点在 i, 左端点在 v, 可以往 i + 1 走, [v, i) += 1, [1, v) U [i, n] -= 1
        {
            ST.range_modify(1, v, i - 1, 1);
            ST.range_modify(1, 1, v - 1, -1);
            ST.range_modify(1, i, n, -1);
        }
        if(ST.tree[1].Min == 0) ans = min(ans, n - ST.tree[1].Sum);
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
题意: 有 n 个城市和 n 条道路围成环形(城市n 和城市1 相连), 现在道路都坏了, 现在有 m 对关系, <i, j> 表示城市 i 和城市 j 必须联通, 
要使所有关系都成立, 至少要维护多少条道路 

注意到, 至少有一条道路可以不被维护, 因为从城市 u 到城市 v 可以走 u -> v, 也可以走 u -> 1 -> v, 因此删掉一条路之后可以绕另一边走
因此, 我们枚举哪条路不用维护, 然后断环成链, 之后给 <i, j> 区间 +1, 最后统计 0 的个数, 即为不用修的路

现在定第 i 条边为城市 i 和城市 i + 1 相连的边, 
当第 i 条边不被维护时, 如果关系 <a, b> 满足 a <= i < b 时, 那么就要走经过边 n -> 1 的路, 否则走另一边
并且发现, 当从小到大枚举第 i 条边不被维护时, 受到影响的关系只有 a == i 和 b == i 的一些关系, 对这些关系进行区间修改即可
如果关系 <a, b> 满足 a <= i < b, 则对区间 [a, b) ± 1, 否则对区间 [1, a) 和 [b, n] ± 1
对于动态区间修改且统计区间 0 的个数, 可以用 Lazy Segment Tree 实现


*/
