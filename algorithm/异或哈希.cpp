#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using namespace std;

// 异或哈希
// 适用范围:
// 1. 判断一个集合 / 区间内每个数出现次数的奇偶性
// 2. 判断两个区间的元素奇偶性特征是否相同
// 3. 把“每个值出现偶数次则抵消”的信息压成一个 u64
//
// 原理:
// 1. 给每个值 x 随机分配一个 64 位权值 h[x]
// 2. 序列中出现一个 x, 就把 h[x] 异或进去
// 3. 因为 a ^ a = 0, 所以同一个值出现偶数次会抵消
//
// 注意:
// 1. 这是随机哈希, 有极低概率冲突
// 2. 若值域未知或很大, 可先离散化
// 3. 若需要可复现结果, 使用固定随机种子

struct XorHash
{
    mt19937_64 rng;
    unordered_map<i64, u64> valHash;
    vector<u64> pre;

    XorHash() : rng(chrono::steady_clock::now().time_since_epoch().count()) {}

    XorHash(const vector<int>& a) : rng(chrono::steady_clock::now().time_since_epoch().count())
    {
        build(a);
    }

    XorHash(const vector<i64>& a) : rng(chrono::steady_clock::now().time_since_epoch().count())
    {
        build(a);
    }

    void resetSeed(u64 seed)
    {
        rng.seed(seed);
        valHash.clear();
        pre.clear();
    }

    u64 getValueHash(i64 x)
    {
        auto it = valHash.find(x);
        if(it != valHash.end()) return it->second;
        u64 h = rng();
        valHash[x] = h;
        return h;
    }

    void build(const vector<int>& a)
    {
        int n = (int)a.size() - 1; // 默认 a[1..n] 有效
        pre.assign(n + 1, 0);
        for(int i = 1; i <= n; i++)
        {
            pre[i] = pre[i - 1] ^ getValueHash(a[i]);
        }
    }

    void build(const vector<i64>& a)
    {
        int n = (int)a.size() - 1; // 默认 a[1..n] 有效
        pre.assign(n + 1, 0);
        for(int i = 1; i <= n; i++)
        {
            pre[i] = pre[i - 1] ^ getValueHash(a[i]);
        }
    }

    // 返回区间 [l, r] 的异或哈希
    // 含义: 只保留每个值出现次数的奇偶性信息
    u64 query(int l, int r) const
    {
        if(l > r) return 0;
        return pre[r] ^ pre[l - 1];
    }

    // 判断两个区间的“奇偶性特征”是否相同
    bool same(int l1, int r1, int l2, int r2) const
    {
        return query(l1, r1) == query(l2, r2);
    }

    // 判断区间 [l, r] 内所有数是否都出现偶数次
    bool allEven(int l, int r) const
    {
        return query(l, r) == 0;
    }
};

/*
使用示例:

1. 判断区间内所有数是否都出现偶数次
vector<int> a(n + 1);
...
XorHash hs(a);
if(hs.allEven(l, r))
{
    ...
}

2. 判断两个区间的奇偶性特征是否相同
if(hs.same(l1, r1, l2, r2))
{
    ...
}

3. 手动获取某个值的随机哈希
u64 hx = hs.getValueHash(x);

说明:
1. query(l, r) 相同, 表示两个区间内每个值出现次数的奇偶性模式相同
2. 不能直接表示精确出现次数, 只能表示奇偶性
3. 若题目要求“出现 k 次”之类更强信息, 通常需要配合别的做法
*/