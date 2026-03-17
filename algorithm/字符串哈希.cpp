#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

// 双哈希
// 用法:
// 1. 字符串下标默认从 1 开始, 即传入的 s 应满足 s[1..n]
// 2. Hash hs(s);
// 3. hs.get(l, r)           -> 获取正向区间哈希
// 4. hs.getRev(l, r)        -> 获取反向区间哈希
// 5. hs.same(l1, r1, l2, r2)-> 判断两个子串是否相等
// 6. hs.isPal(l, r)         -> 判断区间是否是回文串

struct Hash
{
    static const int mod1 = 1000000007;
    static const int mod2 = 1000000009;
    static const i64 P1 = 131;
    static const i64 P2 = 13331;

    int n;
    vector<int> p1, p2;
    vector<int> h1, h2;
    vector<int> rh1, rh2;

    Hash() {}
    Hash(const string& s)
    {
        init(s);
    }

    void init(const string& s)
    {
        n = (int)s.size() - 1;

        p1.assign(n + 1, 0);
        p2.assign(n + 1, 0);
        h1.assign(n + 1, 0);
        h2.assign(n + 1, 0);
        rh1.assign(n + 2, 0);
        rh2.assign(n + 2, 0);

        p1[0] = 1;
        p2[0] = 1;
        for(int i = 1; i <= n; i++)
        {
            p1[i] = (i64)p1[i - 1] * P1 % mod1;
            p2[i] = (i64)p2[i - 1] * P2 % mod2;
            h1[i] = ((i64)h1[i - 1] * P1 + s[i]) % mod1;
            h2[i] = ((i64)h2[i - 1] * P2 + s[i]) % mod2;
        }

        for(int i = n; i >= 1; i--)
        {
            rh1[i] = ((i64)rh1[i + 1] * P1 + s[i]) % mod1;
            rh2[i] = ((i64)rh2[i + 1] * P2 + s[i]) % mod2;
        }
    }

    pair<int, int> get(int l, int r)
    {
        int x = (h1[r] - (i64)h1[l - 1] * p1[r - l + 1] % mod1 + mod1) % mod1;
        int y = (h2[r] - (i64)h2[l - 1] * p2[r - l + 1] % mod2 + mod2) % mod2;
        return {x, y};
    }

    pair<int, int> getRev(int l, int r)
    {
        int x = (rh1[l] - (i64)rh1[r + 1] * p1[r - l + 1] % mod1 + mod1) % mod1;
        int y = (rh2[l] - (i64)rh2[r + 1] * p2[r - l + 1] % mod2 + mod2) % mod2;
        return {x, y};
    }

    bool same(int l1, int r1, int l2, int r2)
    {
        return get(l1, r1) == get(l2, r2);
    }

    bool isPal(int l, int r)
    {
        return get(l, r) == getRev(l, r);
    }
};

/*
示例:

string s;
cin >> s;
s = " " + s;

Hash hs(s);

1. 判断两个子串是否相等
if(hs.same(l1, r1, l2, r2))
{
    ...
}

2. 判断回文
if(hs.isPal(l, r))
{
    ...
}
*/