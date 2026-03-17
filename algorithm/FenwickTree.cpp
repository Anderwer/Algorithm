#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

// 树状数组 / Fenwick Tree
// 适用范围:
// 1. 单点修改 + 前缀查询
// 2. 单点修改 + 区间查询
// 3. 二分前缀和(要求树状数组中维护的前缀和单调不降)
//
// 约定:
// 1. 下标从 1 开始使用
// 2. 若维护普通整数和, T 通常取 int / i64
// 3. 若 T 为自定义类型, 需要支持:
//    - T{}
//    - operator +
//    - operator -
//    - operator <=  (仅 select 使用)

template<typename T>
struct Fenwick
{
    int n;
    vector<T> a;

    Fenwick(int n_ = 0)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        a.assign(n + 1, T{});
    }

    int lowbit(int x)
    {
        return x & -x;
    }

    void add(int pos, const T& val)
    {
        for(int i = pos; i <= n; i += lowbit(i))
        {
            a[i] = a[i] + val;
        }
    }

    T sum(int pos)
    {
        T res{};
        for(int i = pos; i > 0; i -= lowbit(i))
        {
            res = res + a[i];
        }
        return res;
    }

    T get(int l, int r)
    {
        if(l > r) return T{};
        return sum(r) - sum(l - 1);
    }

    // 查询最大的 pos, 使得 sum(pos) <= k
    // 若所有前缀和都大于 k, 返回 0
    int select(const T& k)
    {
        int pos = 0;
        T cur{};
        int lg = 1;
        while((lg << 1) <= n) lg <<= 1;

        for(int d = lg; d > 0; d >>= 1)
        {
            int nxt = pos + d;
            if(nxt <= n && cur + a[nxt] <= k)
            {
                pos = nxt;
                cur = cur + a[nxt];
            }
        }
        return pos;
    }
};

/*
使用示例:

1. 维护前缀和
Fenwick<i64> tr(n);
tr.add(pos, val);
auto pre = tr.sum(pos);
auto seg = tr.get(l, r);

2. 求前缀和不超过 k 的最大位置
int pos = tr.select(k);
*/