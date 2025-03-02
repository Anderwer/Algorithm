#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 1e5 + 10;
int a[N];

template<class Node> //区间乘 + 区间查询 + 单点修改 + 单点查询
struct SegmentTree
{
    #define lc u << 1
    #define rc u << 1 | 1
    const int n, M, p;
    vector<Node> tree;

    SegmentTree(): n(0) {}
    SegmentTree(int n_, int mod): n(n_), M(n * 4 + 10), p(mod)
    {
        tree.reserve(M);
        tree.resize(M);
        build(1, 1, n);
    }

    void build(int u, i64 l, i64 r)
    {
        tree[u].l = l, tree[u].r = r;

        init_lazy(tree[u]);

        if(l == r)
        {
            tree[u] = {l, r, 0, 1, a[l]};
            return; 
        }

        int mid = (l + r) >> 1;
        build(lc, l, mid);
        build(rc, mid + 1, r);
        pushup(tree[u], tree[lc], tree[rc]);
    }

    void pushup(Node& U, Node& L, Node& R)
    {
        U.Sum = (L.Sum + R.Sum) % p;
    }

    void init_lazy(Node& U) 
    {
        U.add = 0;
        U.mul = 1;
    }

    void cal_lazy(Node& Fa, Node& Son)
    {
        Son.Sum = ((Son.Sum * Fa.mul) % p + (Son.r - Son.l + 1) * Fa.add % p) % p;
    }

    void lazy_union(Node& Fa, Node& Son)
    {
        Son.add = (Son.add * Fa.mul % p + Fa.add) % p;
        Son.mul = Son.mul * Fa.mul % p;
    }

    void pushdown(int u) 
    {
        lazy_union(tree[u], tree[lc]);
        cal_lazy(tree[u], tree[lc]);
        lazy_union(tree[u], tree[rc]);
        cal_lazy(tree[u], tree[rc]);
        init_lazy(tree[u]);
    }

    void modify(int u, int pos, int x) //单点修改
    {
        if(tree[u].l >= pos && tree[u].r <= pos)
        {
            tree[u].Sum = x;
            return;
        }
        
        int mid = (tree[u].l + tree[u].r) >> 1;
        if(pos <= mid) modify(lc, pos, x);
        else modify(rc, pos, x);
        pushup(tree[u], tree[lc], tree[rc]);
    }

    i64 query(int u, int pos) //单点查询
    {
        if(pos <= tree[u].l && pos >= tree[u].r) return tree[u].Sum;
        pushdown(u);

        int mid = (tree[u].l + tree[u].r) >> 1;
        i64 sum = 0;
        if(pos <= mid) sum += query(lc, pos);
        if(pos > mid) sum += query(rc, pos);
        return sum;
    }

    void range_modify(int u, int l, int r, int x_add, int x_mul) //区间修改
    {
        if(l <= tree[u].l && r >= tree[u].r)
        {
            tree[u].mul = tree[u].mul * x_mul % p;
            tree[u].add = (tree[u].add * x_mul + x_add) % p;
            tree[u].Sum = (tree[u].Sum * x_mul % p + (tree[u].r - tree[u].l + 1) * x_add % p) % p;
            return;
        }
        pushdown(u);
        
        int mid = (tree[u].l + tree[u].r) >> 1;
        if(l <= mid) range_modify(lc, l, r, x_add, x_mul);
        if(r > mid) range_modify(rc, l, r, x_add, x_mul);
        pushup(tree[u], tree[lc], tree[rc]);
    }
    
    i64 range_query(int u, int l, int r) //区间查询
    {
        if(l <= tree[u].l && r >= tree[u].r) return tree[u].Sum;
        pushdown(u);

        int mid = (tree[u].l + tree[u].r) >> 1;
        i64 sum = 0;
        if(l <= mid) sum = (sum + range_query(lc, l, r)) % p;
        if(r > mid) sum = (sum + range_query(rc, l, r)) % p;
        return sum % p;
    }
};

struct Node
{
    i64 l, r;
    i64 add, mul, Sum;
};


void solve()
{
    int n, q, m;
    cin >> n >> q >> m;
    for(int i = 1; i <= n; i++) cin >> a[i];

    SegmentTree<Node> T(n, m);

    while(q--)
    {
        int op; cin >> op;
        if(op == 1)
        {
            int l, r, x; cin >> l >> r >> x;
            T.range_modify(1, l, r, 0, x);
        }
        else if(op == 2)
        {
            int l, r, x; cin >> l >> r >> x;
            T.range_modify(1, l, r, x, 1);
        }
        else 
        {
            int l, r; cin >> l >> r;
            cout << T.range_query(1, l, r) << "\n";
        }
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
