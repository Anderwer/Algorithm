#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

// ST 表 / Sparse Table
// 适用范围:
// 1. 静态区间可重复贡献查询
// 2. 常见操作: min / max / gcd / lcm / 按位与 / 按位或
// 3. 预处理 O(n log n), 查询 O(1)
//
// 约定:
// 1. 输入数组 a 使用 1 下标, 即 a[1..n] 有效
// 2. Op 需要满足“可重复贡献”, 即:
//    op(x, x) = x
//    并且区间查询可以由两个长度为 2^k 的重叠区间合并得到
//
// 例如:
// 1. min / max / gcd 可以用 ST 表
// 2. 区间和通常不能直接用这种 O(1) ST 查询

template<class T, class F>
struct SparseTable
{
    int n, lg;
    F op;
    vector<int> lg2;
    vector<vector<T>> st;

    SparseTable() {}
    SparseTable(const vector<T>& a, F f)
    {
        init(a, f);
    }

    void init(const vector<T>& a, F f)
    {
        op = f;
        n = (int)a.size() - 1;
        lg = 0;
        while((1 << lg) <= n) lg++;

        lg2.assign(n + 1, 0);
        for(int i = 2; i <= n; i++) lg2[i] = lg2[i >> 1] + 1;

        st.assign(lg, vector<T>(n + 1));
        for(int i = 1; i <= n; i++) st[0][i] = a[i];

        for(int j = 1; j < lg; j++)
        {
            for(int i = 1; i + (1 << j) - 1 <= n; i++)
            {
                st[j][i] = op(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    T query(int l, int r) const
    {
        int k = lg2[r - l + 1];
        return op(st[k][l], st[k][r - (1 << k) + 1]);
    }
};


// 常用运算
struct MinOp
{
    template<class T>
    T operator()(const T& a, const T& b) const
    {
        return min(a, b);
    }
};

struct MaxOp
{
    template<class T>
    T operator()(const T& a, const T& b) const
    {
        return max(a, b);
    }
};

struct GcdOp
{
    int operator()(int a, int b) const
    {
        return gcd(a, b);
    }

    i64 operator()(i64 a, i64 b) const
    {
        return gcd(a, b);
    }
};

struct AndOp
{
    template<class T>
    T operator()(const T& a, const T& b) const
    {
        return a & b;
    }
};

struct OrOp
{
    template<class T>
    T operator()(const T& a, const T& b) const
    {
        return a | b;
    }
};

/*
使用示例:

1. 区间最小值
vector<int> a(n + 1);
...
SparseTable<int, MinOp> stMin(a, MinOp());
cout << stMin.query(l, r) << "\n";

2. 区间最大值
SparseTable<int, MaxOp> stMax(a, MaxOp());
cout << stMax.query(l, r) << "\n";

3. 区间 gcd
SparseTable<int, GcdOp> stGcd(a, GcdOp());
cout << stGcd.query(l, r) << "\n";

4. 自定义运算
auto op = [&](int x, int y)
{
    return min(x, y);
};
SparseTable<int, decltype(op)> st(a, op);

补充:
1. 区间 [L, R] 的 gcd 可以结合差分使用:
   gcd(a[L], a[L + 1], ..., a[R])
   = gcd(a[L], |a[L + 1] - a[L]|, ..., |a[R] - a[R - 1]|)

2. 若题目有修改操作, ST 表一般不适合, 优先考虑线段树
*/