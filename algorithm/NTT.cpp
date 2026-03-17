#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

// NTT 模板
// 说明:
// 1. 默认模数为 998244353, 原根为 3
// 2. 适用于模意义下多项式卷积
// 3. 传入的多项式系数下标默认从 0 开始
// 4. conv(a, b) 返回 a 和 b 的卷积结果, 下标仍从 0 开始

struct NTT
{
    static const int mod = 998244353;
    static const int G = 3;

    i64 qpow(i64 a, i64 b)
    {
        i64 res = 1;
        while(b)
        {
            if(b & 1) res = res * a % mod;
            a = a * a % mod;
            b >>= 1;
        }
        return res;
    }

    void dft(vector<i64>& a, int type)
    {
        int n = a.size();
        vector<int> rev(n);
        int lg = 0;
        while((1 << lg) < n) lg++;

        for(int i = 0; i < n; i++)
        {
            rev[i] = 0;
            for(int j = 0; j < lg; j++)
            {
                if(i >> j & 1) rev[i] |= 1 << (lg - 1 - j);
            }
            if(i < rev[i]) swap(a[i], a[rev[i]]);
        }

        for(int len = 2; len <= n; len <<= 1)
        {
            i64 wn = qpow(type == 1 ? G : qpow(G, mod - 2), (mod - 1) / len);
            for(int i = 0; i < n; i += len)
            {
                i64 w = 1;
                for(int j = 0; j < (len >> 1); j++)
                {
                    i64 x = a[i + j];
                    i64 y = w * a[i + j + (len >> 1)] % mod;
                    a[i + j] = (x + y) % mod;
                    a[i + j + (len >> 1)] = (x - y + mod) % mod;
                    w = w * wn % mod;
                }
            }
        }

        if(type == -1)
        {
            i64 inv = qpow(n, mod - 2);
            for(int i = 0; i < n; i++) a[i] = a[i] * inv % mod;
        }
    }

    vector<i64> conv(vector<i64> a, vector<i64> b)
    {
        if(a.empty() || b.empty()) return {};

        int n = a.size(), m = b.size();
        int len = 1;
        while(len < n + m - 1) len <<= 1;

        a.resize(len);
        b.resize(len);

        for(auto& x : a) x = (x % mod + mod) % mod;
        for(auto& x : b) x = (x % mod + mod) % mod;

        dft(a, 1);
        dft(b, 1);
        for(int i = 0; i < len; i++) a[i] = a[i] * b[i] % mod;
        dft(a, -1);

        a.resize(n + m - 1);
        return a;
    }
};

/*
使用示例:

NTT ntt;
vector<i64> a = {1, 2, 3};
vector<i64> b = {4, 5, 6};
auto c = ntt.conv(a, b);

此时:
c[0] = 4
c[1] = 13
c[2] = 28
c[3] = 27
c[4] = 18
*/