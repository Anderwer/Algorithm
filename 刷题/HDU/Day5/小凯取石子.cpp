#include <bits/stdc++.h>
#define int long long
using i64 = long long;
using namespace std;
const int p = 998244353;

array<i64, 2> add(array<i64, 2> a, array<i64, 2> b)
{
    array<i64, 2> res = {a[0] * b[1] + b[0] * a[1], a[1] * b[1]};
    if(res[0] == 0) return res;
    i64 g = __gcd(res[0], res[1]);
    return {res[0] / g, res[1] / g};
}

array<i64, 2> mul(array<i64, 2> a, array<i64, 2> b)
{
    array<i64, 2> res = {a[0] * b[0], a[1] * b[1]};
    if(res[0] == 0) return res;
    i64 g = __gcd(res[0], res[1]);
    return {res[0] / g, res[1] / g};
}

void print(array<i64, 2> a)
{
    cout << a[0] << "/" << a[1];
}

array<i64, 2> Max(array<i64, 2> a, array<i64, 2> b)
{
    if(a[0] * b[1] >= a[1] * b[0]) return a;
    return b;
}

void init()
{
    int n = 1e5;
    vector<array<i64, 2>> f(n + 1);
    vector<array<i64, 2>> g(n + 1);
    f[0] = {1, 1};
    g[0] = {0, 1};
    f[1] = {1, 2}, g[1] = {1, 1};
    f[2] = {1, 1}, g[2] = {1, 2};
    f[3] = {3, 4}, g[3] = {1, 1};
    f[4] = {1, 2}, g[4] = {1, 1};

    for(int i = 5; i < n; i++)
    {
        f[i] = add(mul({1ll, 2ll}, g[i - 1]), mul({1ll, 2ll}, g[i - 4]));
        g[i] = Max(f[i - 1], f[i - 4]);
    }
    
    for(int i = 1; i < n; i++)
    {
        cout << "i = " << i << "时, f[i] = ";
        print(f[i]);
        cout << "\n";
    }
}

i64 qpow(i64 a, i64 b)
{
	i64 res = 1;
	while(b)
	{
		if(b & 1) res = res * a % p;
		a = a * a % p;
		b >>= 1; 
	}
	return res % p;
}


void solve()
{
    i64 n;
    cin >> n;
    i64 inv_2 = 499122177;

    vector<i64> f(5);
    f[1] = inv_2;
    f[2] = 1;
    f[3] = 3 * qpow(4, p - 2) % p;
    f[4] = inv_2;
    if(n <= 4) cout << f[n] << "\n";
    else 
    {
        if(n % 5 == 0 || n % 5 == 2) cout << 1 << "\n";
        else if(n % 5 == 1) cout << (1ll + p - qpow(qpow(2, n / 5), p - 2) + p) % p << "\n";
        else if(n % 5 == 4) cout << (1ll + p - qpow(qpow(2, n / 5 + 1), p - 2) + p) % p << "\n";
        else if(n % 5 == 3) cout << (1ll + p - qpow(qpow(2, n / 5 + 2), p - 2) + p) % p << "\n";
    }

}

// 设 f[i]: 轮到 Kc0 走且还剩 i 个石子时小凯最终获胜的概率
// 设 g[i]: 轮到 小凯 走且还剩 i 个石子时小凯最终获胜的概率
// 初始 f(0) = 1, g(0) = 0

// 手玩一下发现:
// f(1) = 1/2    g(1) = f(0) = 1
// f(2) = 0.5 * g(1) + 0.5 * 1 = 1    g(2) = f(1) = 1/2
// f(3) = 0.5 * g(2) + 0.5 * 1 = 3/4    g(3) = f(2) = 1
// f(4) = 0.5 * g(3) + 0.5 * g(0) =  1/2    g(4) = max(f(3), f(0)) = 1
// f(5) = 0.5 * g(4) + 0.5 * g(1) = 1, g(5) = max(f(4), f(1)) = 1

// 显然有转移 f(i) = 0.5 * g(i - 1) + 0.5 * g(i - 4)
//           g(i) = max(f(i - 1), f(i - 4)) (i >= 4)


// 经过打表发现, 当 n % 5 == 0 || n % 5 == 2 时 f[i] = 1
// 当 n % 5 == 1 时 f[i] = 1 - (1 / 2 ^ k), 其中 k = (n / 5)
// 当 n % 5 == 4 时 f[i] = 1 - (1 / 2 ^ (k + 1))
// 当 n % 5 == 3 时 f[i] = 1 - (1 / 2 ^ (k + 2))
// 特判 f[1], f[2], f[3], f[4]

signed main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--)
    {
        solve();
    }
    return 0;
}
