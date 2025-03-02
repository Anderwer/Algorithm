
template<class Node> //单点修改 + 区间查询 (最大值为例)
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
        tree[u].l = l, tree[u].r = r;
        if(l == r)
        {
            tree[u] = {l, r, a[l]};
            return; 
        }

        int mid = (l + r) >> 1;
        build(lc, l, mid);
        build(rc, mid + 1, r);
        pushup(tree[u], tree[lc], tree[rc]);
    }

    void pushup(Node& U, Node& L, Node& R)
    {
        U.Max = max(L.Max, R.Max);
    }

    void modify(int u, int pos, int x) //单点修改
    {
        if(tree[u].l >= pos && tree[u].r <= pos)
        {
            tree[u].Max = x;
            return;
        }
        
        int mid = (tree[u].l + tree[u].r) >> 1;
        if(pos <= mid) modify(lc, pos, x);
        else modify(rc, pos, x);
        pushup(tree[u], tree[lc], tree[rc]);
    }

    i64 query(int u, int l, int r) //区间查询
    {
        if(l <= tree[u].l && r >= tree[u].r) return tree[u].Max;

        i64 Max = -1e18;
        int mid = (tree[u].l + tree[u].r) >> 1;
        if(l <= mid) Max = max(Max, query(lc, l, r));
        if(r > mid) Max = max(Max, query(rc, l, r));
        return Max;
    }
};
struct Node
{
    i64 l, r;
    i64 Max;
};


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
        tree[u].l = l, tree[u].r = r;

        init_lazy(tree[u]);

        if(l == r)
        {
            tree[u] = {l, r, 0, a[l]};
            return; 
        }

        int mid = (l + r) >> 1;
        build(lc, l, mid);
        build(rc, mid + 1, r);
        pushup(tree[u], tree[lc], tree[rc]);
    }

    void pushup(Node& U, Node& L, Node& R)
    {
        U.Sum = L.Sum + R.Sum;
    }

    void init_lazy(Node& U) 
    {
        U.add = 0;
    }

    void cal_lazy(Node& Fa, Node& Son)
    {
        Son.Sum += (Son.r - Son.l + 1) * Fa.add;
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

    void range_modify(int u, int l, int r, int x) //区间修改
    {
        if(l <= tree[u].l && r >= tree[u].r)
        {
            tree[u].Sum += (tree[u].r - tree[u].l + 1) * x;
            tree[u].add += x;
            return;
        }
        pushdown(u);
        
        int mid = (tree[u].l + tree[u].r) >> 1;
        if(l <= mid) range_modify(lc, l, r, x);
        if(r > mid) range_modify(rc, l, r, x);
        pushup(tree[u], tree[lc], tree[rc]);
    }
    
    i64 range_query(int u, int l, int r) //区间查询
    {
        if(l <= tree[u].l && r >= tree[u].r) return tree[u].Sum;
        pushdown(u);

        int mid = (tree[u].l + tree[u].r) >> 1;
        i64 sum = 0;
        if(l <= mid) sum += range_query(lc, l, r);
        if(r > mid) sum += range_query(rc, l, r);
        return sum;
    }
};

struct Node
{
    i64 l, r;
    i64 add, Sum;
};


template<class Node> //区间乘(余p) + 区间查询 + 单点修改 + 单点查询
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

--------------------------------------------------------------------------------------------------------

template<class Node> //区间修改 + 区间查询 0 的个数
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
