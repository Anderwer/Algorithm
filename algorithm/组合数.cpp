#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

// 组合数模板集合
// 包含:
// 1. 快速幂
// 2. 预处理阶乘 + 逆阶乘求组合数
// 3. Lucas 定理(模数为质数)
// 4. Pascal 递推求小范围组合数
//
// 说明:
// 1. 若需要频繁查询 C(n, k) 且 n 不大, 优先使用 Comb
// 2. 若 n 很大、模数 p 为质数, 可使用 Lucas
// 3. 所有模板默认模数为质数时可用逆元写法
// 4. 点开即抄即可, 不依赖额外全局变量

i64 qpow(i64 a, i64 b, i64 mod)
{
    a %= mod;
    if(a < 0) a += mod;
    i64 res = 1 % mod;
    while(b)
    {
        if(b & 1) res = (__int128)res * a % mod;
        a = (__int128)a * a % mod;
        b >>= 1;
    }
    return res;
}


// 预处理阶乘 + 逆阶乘
// 适用于多次查询 C(n, k), 且 n 的上界已知
struct Comb
{
    int n;
    i64 mod;
    vector<i64> fact, ifact;

    Comb() {}
    Comb(int n_, i64 mod_)
    {
        init(n_, mod_);
    }

    void init(int n_, i64 mod_)
    {
        n = n_;
        mod = mod_;
        fact.assign(n + 1, 1);
        ifact.assign(n + 1, 1);

        for(int i = 1; i <= n; i++)
        {
            fact[i] = fact[i - 1] * i % mod;
        }

        ifact[n] = qpow(fact[n], mod - 2, mod);
        for(int i = n - 1; i >= 0; i--)
        {
            ifact[i] = ifact[i + 1] * (i + 1) % mod;
        }
    }

    i64 C(int n_, int k_) const
    {
        if(k_ < 0 || k_ > n_) return 0;
        if(n_ < 0 || n_ > n) return 0;
        return fact[n_] * ifact[k_] % mod * ifact[n_ - k_] % mod;
    }

    i64 A(int n_, int k_) const
    {
        if(k_ < 0 || k_ > n_) return 0;
        if(n_ < 0 || n_ > n) return 0;
        return fact[n_] * ifact[n_ - k_] % mod;
    }
};


// Lucas 定理
// 适用于求 C(n, k) mod p, 其中 p 为质数, n 和 k 可能很大
struct Lucas
{
    i64 mod;

    Lucas() {}
    Lucas(i64 mod_)
    {
        init(mod_);
    }

    void init(i64 mod_)
    {
        mod = mod_;
    }

    i64 smallC(i64 n, i64 k) const
    {
        if(k < 0 || k > n) return 0;
        if(k > n - k) k = n - k;

        i64 ans = 1;
        for(i64 i = 1; i <= k; i++)
        {
            ans = (__int128)ans * (n - k + i) % mod;
            ans = (__int128)ans * qpow(i, mod - 2, mod) % mod;
        }
        return ans;
    }

    i64 C(i64 n, i64 k) const
    {
        if(k < 0 || k > n) return 0;
        if(n < mod && k < mod) return smallC(n, k);
        return C(n / mod, k / mod) * smallC(n % mod, k % mod) % mod;
    }
};


// Pascal 递推
// 适用于 n 较小, 且不一定要求模数是质数
struct PascalComb
{
    int n;
    i64 mod;
    vector<vector<i64>> c;

    PascalComb() {}
    PascalComb(int n_, i64 mod_)
    {
        init(n_, mod_);
    }

    void init(int n_, i64 mod_)
    {
        n = n_;
        mod = mod_;
        c.assign(n + 1, vector<i64>(n + 1, 0));

        for(int i = 0; i <= n; i++)
        {
            c[i][0] = c[i][i] = 1 % mod;
            for(int j = 1; j < i; j++)
            {
                c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
            }
        }
    }

    i64 C(int n_, int k_) const
    {
        if(k_ < 0 || k_ > n_) return 0;
        if(n_ < 0 || n_ > n) return 0;
        return c[n_][k_];
    }
};


/*
使用示例:

1. 多次查询组合数
const int mod = 998244353;
Comb comb(200000, mod);
cout << comb.C(n, k) << "\n";
cout << comb.A(n, k) << "\n";

2. Lucas 定理
Lucas lucas(1000003); // p 必须是质数
cout << lucas.C(n, k) << "\n";

3. Pascal 递推
PascalComb pc(5000, mod);
cout << pc.C(n, k) << "\n";

常见公式:
1. C(n, k) = C(n - 1, k - 1) + C(n - 1, k)
2. C(n, k) = C(n, n - k)
3. A(n, k) = n! / (n - k)!
4. C(n, k) = n! / (k! * (n-k)!)

注意:
1. Comb 和 Lucas 默认都依赖逆元, 因此模数应为质数
2. 若模数不是质数, 优先考虑 Pascal 递推或 exgcd 相关方法
3. Lucas 适合单次或少量大范围查询, 若 p 很大则 smallC 常数也会变大
*/