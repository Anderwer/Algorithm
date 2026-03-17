#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

// 线段树模板集合
// 约定:
// 1. 输入数组 a 使用 1 下标, 即 a[1..n]
// 2. 需要什么模板就复制对应结构体即可
// 3. 所有接口均为竞赛常用写法


// 单点修改 + 区间最大值查询
struct SegmentTreeMax
{
    struct Node
    {
        int l, r;
        i64 mx;
    };

    int n;
    vector<Node> tr;

    SegmentTreeMax() {}
    SegmentTreeMax(const vector<i64>& a)
    {
        init(a);
    }

    void init(const vector<i64>& a)
    {
        n = (int)a.size() - 1;
        tr.assign(n * 4 + 10, {});
        build(1, 1, n, a);
    }

    void pushup(int u)
    {
        tr[u].mx = max(tr[u << 1].mx, tr[u << 1 | 1].mx);
    }

    void build(int u, int l, int r, const vector<i64>& a)
    {
        tr[u].l = l;
        tr[u].r = r;
        if(l == r)
        {
            tr[u].mx = a[l];
            return;
        }

        int mid = (l + r) >> 1;
        build(u << 1, l, mid, a);
        build(u << 1 | 1, mid + 1, r, a);
        pushup(u);
    }

    void modify(int u, int pos, i64 val)
    {
        if(tr[u].l == tr[u].r)
        {
            tr[u].mx = val;
            return;
        }

        int mid = (tr[u].l + tr[u].r) >> 1;
        if(pos <= mid) modify(u << 1, pos, val);
        else modify(u << 1 | 1, pos, val);
        pushup(u);
    }

    i64 query(int u, int l, int r)
    {
        if(l <= tr[u].l && tr[u].r <= r) return tr[u].mx;

        i64 res = -(i64)4e18;
        int mid = (tr[u].l + tr[u].r) >> 1;
        if(l <= mid) res = max(res, query(u << 1, l, r));
        if(r > mid) res = max(res, query(u << 1 | 1, l, r));
        return res;
    }
};


// 区间加 + 区间求和
struct SegmentTreeSumAdd
{
    struct Node
    {
        int l, r;
        i64 sum, add;
    };

    int n;
    vector<Node> tr;

    SegmentTreeSumAdd() {}
    SegmentTreeSumAdd(const vector<i64>& a)
    {
        init(a);
    }

    void init(const vector<i64>& a)
    {
        n = (int)a.size() - 1;
        tr.assign(n * 4 + 10, {});
        build(1, 1, n, a);
    }

    void pushup(int u)
    {
        tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
    }

    void apply(int u, i64 val)
    {
        tr[u].sum += 1LL * (tr[u].r - tr[u].l + 1) * val;
        tr[u].add += val;
    }

    void pushdown(int u)
    {
        if(tr[u].add == 0) return;
        apply(u << 1, tr[u].add);
        apply(u << 1 | 1, tr[u].add);
        tr[u].add = 0;
    }

    void build(int u, int l, int r, const vector<i64>& a)
    {
        tr[u].l = l;
        tr[u].r = r;
        tr[u].add = 0;
        if(l == r)
        {
            tr[u].sum = a[l];
            return;
        }

        int mid = (l + r) >> 1;
        build(u << 1, l, mid, a);
        build(u << 1 | 1, mid + 1, r, a);
        pushup(u);
    }

    void modify(int u, int pos, i64 val)
    {
        if(tr[u].l == tr[u].r)
        {
            tr[u].sum = val;
            tr[u].add = 0;
            return;
        }

        pushdown(u);
        int mid = (tr[u].l + tr[u].r) >> 1;
        if(pos <= mid) modify(u << 1, pos, val);
        else modify(u << 1 | 1, pos, val);
        pushup(u);
    }

    i64 query(int u, int pos)
    {
        if(tr[u].l == tr[u].r) return tr[u].sum;
        pushdown(u);
        int mid = (tr[u].l + tr[u].r) >> 1;
        if(pos <= mid) return query(u << 1, pos);
        return query(u << 1 | 1, pos);
    }

    void range_modify(int u, int l, int r, i64 val)
    {
        if(l <= tr[u].l && tr[u].r <= r)
        {
            apply(u, val);
            return;
        }

        pushdown(u);
        int mid = (tr[u].l + tr[u].r) >> 1;
        if(l <= mid) range_modify(u << 1, l, r, val);
        if(r > mid) range_modify(u << 1 | 1, l, r, val);
        pushup(u);
    }

    i64 range_query(int u, int l, int r)
    {
        if(l <= tr[u].l && tr[u].r <= r) return tr[u].sum;

        pushdown(u);
        i64 res = 0;
        int mid = (tr[u].l + tr[u].r) >> 1;
        if(l <= mid) res += range_query(u << 1, l, r);
        if(r > mid) res += range_query(u << 1 | 1, l, r);
        return res;
    }
};


// 区间乘 + 区间加 + 区间求和(mod p)
// 维护仿射变换: x -> x * mul + add
struct SegmentTreeAffineSum
{
    struct Node
    {
        int l, r;
        i64 sum, add, mul;
    };

    int n, mod;
    vector<Node> tr;

    SegmentTreeAffineSum() {}
    SegmentTreeAffineSum(const vector<i64>& a, int p)
    {
        init(a, p);
    }

    void init(const vector<i64>& a, int p)
    {
        n = (int)a.size() - 1;
        mod = p;
        tr.assign(n * 4 + 10, {});
        build(1, 1, n, a);
    }

    void pushup(int u)
    {
        tr[u].sum = (tr[u << 1].sum + tr[u << 1 | 1].sum) % mod;
    }

    void apply(int u, i64 add, i64 mul)
    {
        tr[u].sum = (tr[u].sum * mul % mod + 1LL * (tr[u].r - tr[u].l + 1) * add % mod) % mod;
        tr[u].mul = tr[u].mul * mul % mod;
        tr[u].add = (tr[u].add * mul % mod + add) % mod;
    }

    void pushdown(int u)
    {
        if(tr[u].mul == 1 && tr[u].add == 0) return;
        apply(u << 1, tr[u].add, tr[u].mul);
        apply(u << 1 | 1, tr[u].add, tr[u].mul);
        tr[u].add = 0;
        tr[u].mul = 1;
    }

    void build(int u, int l, int r, const vector<i64>& a)
    {
        tr[u].l = l;
        tr[u].r = r;
        tr[u].add = 0;
        tr[u].mul = 1;
        if(l == r)
        {
            tr[u].sum = (a[l] % mod + mod) % mod;
            return;
        }

        int mid = (l + r) >> 1;
        build(u << 1, l, mid, a);
        build(u << 1 | 1, mid + 1, r, a);
        pushup(u);
    }

    void modify(int u, int pos, i64 val)
    {
        if(tr[u].l == tr[u].r)
        {
            tr[u].sum = (val % mod + mod) % mod;
            tr[u].add = 0;
            tr[u].mul = 1;
            return;
        }

        pushdown(u);
        int mid = (tr[u].l + tr[u].r) >> 1;
        if(pos <= mid) modify(u << 1, pos, val);
        else modify(u << 1 | 1, pos, val);
        pushup(u);
    }

    i64 query(int u, int pos)
    {
        if(tr[u].l == tr[u].r) return tr[u].sum;
        pushdown(u);
        int mid = (tr[u].l + tr[u].r) >> 1;
        if(pos <= mid) return query(u << 1, pos);
        return query(u << 1 | 1, pos);
    }

    void range_modify(int u, int l, int r, i64 add, i64 mul)
    {
        add = (add % mod + mod) % mod;
        mul = (mul % mod + mod) % mod;
        if(l <= tr[u].l && tr[u].r <= r)
        {
            apply(u, add, mul);
            return;
        }

        pushdown(u);
        int mid = (tr[u].l + tr[u].r) >> 1;
        if(l <= mid) range_modify(u << 1, l, r, add, mul);
        if(r > mid) range_modify(u << 1 | 1, l, r, add, mul);
        pushup(u);
    }

    i64 range_query(int u, int l, int r)
    {
        if(l <= tr[u].l && tr[u].r <= r) return tr[u].sum;

        pushdown(u);
        i64 res = 0;
        int mid = (tr[u].l + tr[u].r) >> 1;
        if(l <= mid) res = (res + range_query(u << 1, l, r)) % mod;
        if(r > mid) res = (res + range_query(u << 1 | 1, l, r)) % mod;
        return res;
    }
};


/*
使用示例:

1. 单点修改 + 区间最大值
vector<i64> a(n + 1);
SegmentTreeMax seg(a);
seg.modify(1, pos, val);
cout << seg.query(1, l, r) << "\n";

2. 区间加 + 区间求和
vector<i64> a(n + 1);
SegmentTreeSumAdd seg(a);
seg.range_modify(1, l, r, val);
cout << seg.range_query(1, l, r) << "\n";

3. 区间乘 + 区间加 + 区间求和(mod p)
vector<i64> a(n + 1);
SegmentTreeAffineSum seg(a, mod);
seg.range_modify(1, l, r, add, mul);
cout << seg.range_query(1, l, r) << "\n";
*/