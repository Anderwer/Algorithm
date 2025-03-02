#include <bits/stdc++.h>
#define int long long
using i64 = long long;
using namespace std;
const int N = 2e5 + 10;
const int p = 1e9 + 7;
int a[N];
int fact[N + 1], infact[N + 1];

int qpow(int a, int b)
{
    int res = 1;
    while(b)
    {
        if(b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res % p;
}

void IComb()
{
    fact[0] = 1;
    for(int i = 1; i <= N; i++) fact[i] = (fact[i - 1] * i) % p;
    infact[N] = qpow(fact[N], p - 2);
    for(int i = N - 1; i >= 0; i--) infact[i] = (infact[i + 1] * (i + 1)) % p;
}

int C(int a, int b)
{
    if(b > a || b < 0) return 0;
    return (fact[a] * ((infact[b] * infact[a - b]) % p)) % p;
}

void solve()
{
    int n, k;
    cin >> n >> k;
    int cnt_0 = 0, cnt_1 = 0;
    for(int i = 1; i <= n; i++) cin >> a[i], cnt_0 += (a[i] == 0), cnt_1 += (a[i] == 1);

    int ans = C(n, k);
    for(int i = (k + 1) / 2; i <= min(cnt_0, k); i++)
    {
        ans = (ans - C(cnt_0, i) * C(cnt_1, k - i) % p + p) % p;
    }
    cout << ans << "\n";

}

signed main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    cin >> t;
    IComb();
    while(t--){
        solve();
    }
    return 0;
}
