#include <bits/stdc++.h>
#define int long long
using i64 = long long;
using namespace std;
const int N = 5e5 + 10;

i64 a[N];

void solve()
{
    i64 n, x, mx = 0;
    i64 sum = 0;
    cin >> n >> x;
    for(int i = 1; i <= n; i++) cin >> a[i], sum += a[i], mx = max(a[i], mx);
    int ans = max(mx, (sum + x - 1LL) / x);
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
找到 a 中最大的数 a[i]
至少有 a[i] 个人要买这辆车

*/