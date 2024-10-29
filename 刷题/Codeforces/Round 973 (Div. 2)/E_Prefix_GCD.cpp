#include <bits/stdc++.h>
#define int long long
using i64 = long long;
using namespace std;
const int N = 2e5 + 10;
int a[N];

void solve()
{
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];

    int g = 0, now_gcd = 0;
    for(int i = 1; i <= n; i++) g = gcd(g, a[i]);

    int cnt = 0;
    i64 ans = 0;
    while(true)
    {
        int min_gcd = 1e9;
        for(int i = 1; i <= n; i++) min_gcd = min(min_gcd, gcd(now_gcd, a[i]));
        ans += min_gcd;
        now_gcd = min_gcd;
        cnt++;
        if(now_gcd == g) break;
    }
    ans += (n - cnt) * g;
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
要找 gcd 前缀最小
因为 a[i] <= 1e5, 所以 gcd 最大 <= 1e5
每次加一个数进去, 都会至少使 now_gcd / 2, 因此加入至多 log2(1e5) ~= 13 次就会使 now_gcd = gcd(a1, a2, ..., an)
假如选了 x 个数之后有 now_gcd = gcd(a1, a2, ..., an), 则后面 n - x 次 的贡献都是 gcd(a1, a2, ..., an)
考虑暴力即可 O(13n)

*/