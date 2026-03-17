#include <bits/stdc++.h>
#define int long long
using i64 = long long;
using namespace std;
const int N = 2e5 + 10;
const int mod = 1e9 + 7;
const i64 inv_10000 = 285700002ll;

int a[N], p[N];
i64 f[2][1100];
int qpow(i64 a, int b)
{
    int res = 1;
    while(b)
    {
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res % mod;
}

void solve()
{
    int n;
    cin >> n;
    for(int i = 0; i <= 1024; i++) f[0][i] = f[1][i] = 0;
    f[0][0] = 1;

    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) cin >> p[i];

    for(int i = 1; i <= n; i++)
    {
        for(int j = 0; j <= 1023; j++)
        {
            f[i & 1][j] = (f[(i - 1) & 1][j] * (10000 - p[i]) % mod * inv_10000 % mod + f[(i - 1) & 1][j ^ a[i]] * p[i] % mod * inv_10000 % mod) % mod;
        }
    }

    int ans = 0;
    for(int i = 0; i <= 1024; i++) //枚举异或和
    {
        ans = (ans + i * f[n & 1][i] % mod * i % mod + mod) % mod;
    }
    cout << ans << "\n";
}
signed main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
/*
由异或和越来越小的规律和 1 <= a[i] <= 1023 可以发现, 异或和 <= 1023

为了求 f(s)^2 的期望, 可以先求 P(s), EX(s) = P(s) * f(s)^2

P(s) 可以用概率dp 推得
设 f[i][j] 为 到前 i 个数为止, 异或和为 j 的概率
状态转移 : f[i][j] = f[i - 1][j] * (1 - p[i] / 10000) + f[i - 1][j ^ a[i]] * (p[i] / 10000)
取模状态下: f[i][j] = (f[i - 1][j] * (10000 - p[i]) * qpow(10000, mod) % mod + f[i - 1][j ^ a[i]] * (10000 - p[i]) * qpow(10000, mod) % mod) % mod;
注意到, f[i][j]的状态转移只与 f[i - 1]有关, 因此可以把 f[i - 1] 前面的全部优化掉, 利用 f[i & 1] 的特性
*/