#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

const int N = 5e6 + 10;
int a[N], s[N], sv[N], inv[N];
i64 n, p, k;

template <typename T>
inline void read(T &x)//快读
{
    char c;
    x = 0;
    int fu = 1;
    c = getchar();
    while(c > 57 || c < 48)
    {
        if(c == 45)
        {
            fu = -1;
        }
        c = getchar();
    }
    while(c <= 57 && c >= 48)
    {
        x = (x << 3) + (x << 1) + c - 48;
        c = getchar();
    }
    x *= fu;
}

int qpow(i64 a, int b)
 {
    int ans = 1;
    a = (a % p + p) % p;
    for (; b; b >>= 1)
    {
        if (b & 1) ans = (i64)(a * ans) % p;
        a = (i64)(a * a) % p;
    }
    return ans % p;
}

void get_inv()
{
    s[0] = 1;
    for(int i = 1; i <= n; i++) s[i] = ((i64)s[i - 1] * (i64)a[i]) % p;
    sv[n] = qpow(s[n], p - 2);
    for(int i = n; i >= 1; i--) sv[i - 1] = ((i64)sv[i] * (i64)a[i]) % p;
    for(int i = 1; i <= n; i++) inv[i] = ((i64)sv[i] * (i64)s[i - 1]) % p;
}

void solve()
{
    read(n);
    read(p);
    read(k);
    for(int i = 1; i <= n; i++) read(a[i]);
    get_inv();
    i64 ans = 0, kk = 1;
    for(int i = 1; i <= n; i++)
    {
        kk = (i64)(kk * k) % p;
        ans += (i64)(kk * inv[i]) % p;
        ans %= p;
    }
    cout << (ans % p + p) % p<< '\n';
}

signed main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    solve();
    return 0;
}