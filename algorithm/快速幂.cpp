#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

// 模运算相关函数
// 适用于算法竞赛中常见的:
// 1. 快速幂
// 2. 快速乘(防止 i64 乘法溢出)
// 3. exgcd 求逆元
// 4. 费马小定理求逆元(模数为质数)
// 5. 线性求 1..n 的逆元(模数为质数)

i64 norm(i64 x, i64 mod)
{
    x %= mod;
    if(x < 0) x += mod;
    return x;
}

i64 qpow(i64 a, i64 b, i64 mod)
{
    a = norm(a, mod);
    i64 res = 1 % mod;
    while(b)
    {
        if(b & 1) res = (__int128)res * a % mod;
        a = (__int128)a * a % mod;
        b >>= 1;
    }
    return res;
}

// 当 a * b 可能爆 i64 时使用
i64 qmul(i64 a, i64 b, i64 mod)
{
    a = norm(a, mod);
    b = norm(b, mod);
    i64 res = 0;
    while(b)
    {
        if(b & 1) res = (res + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return res;
}

i64 exgcd(i64 a, i64 b, i64& x, i64& y)
{
    if(b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    i64 d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

// exgcd 求逆元, 要求 gcd(a, mod) = 1
i64 inv_exgcd(i64 a, i64 mod)
{
    i64 x, y;
    i64 d = exgcd(a, mod, x, y);
    if(d != 1) return -1; // 逆元不存在
    return norm(x, mod);
}

// 费马小定理求逆元, 要求 mod 是质数 且 a % mod != 0
i64 inv_qpow(i64 a, i64 mod)
{
    return qpow(a, mod - 2, mod);
}

// 线性求 1..n 的逆元
// 要求 mod 是质数
vector<i64> get_inv(int n, i64 mod)
{
    vector<i64> inv(n + 1);
    if(n >= 1) inv[1] = 1;
    for(int i = 2; i <= n; i++)
    {
        inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    }
    return inv;
}

/*
常用写法:

1. 快速幂
i64 x = qpow(a, b, mod);

2. 快速乘
i64 x = qmul(a, b, mod);

3. exgcd 求逆元
i64 inva = inv_exgcd(a, mod);

4. 费马小定理求逆元
i64 inva = inv_qpow(a, mod);

5. 线性求 1..n 的逆元
auto inv = get_inv(n, mod);
*/