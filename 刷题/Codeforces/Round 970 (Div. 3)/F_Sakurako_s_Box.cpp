#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

const int N = 2e5 + 10;
const int p = 1e9 + 7;
i64 a[N];
i64 pre[N];

i64 qpow(i64 a, int b)
{
    int sum = 1;
    while(b)
    {
        if(b & 1) sum = sum * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return sum;
}

void solve()
{
    i64 n;
    cin >> n;
    pre[0] = 0;
    for(int i = 1; i <= n; i++) cin >> a[i];
    i64 c = n * (n - 1) / 2;
    c %= p;
    for(int i = 1; i <= n; i++) pre[i] = (pre[i - 1] + a[i]) % p;
    i64 x = 0;
    for(int i = 1; i < n; i++)
    {
        x = (x + ((a[i] % p) * ((pre[n] - pre[i]) % p)) % p) % p;
    }
    i64 ans = ((x * qpow(c, p - 2)) % p + p) % p;
    cout << ans << "\n"; 
}
int main()
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
