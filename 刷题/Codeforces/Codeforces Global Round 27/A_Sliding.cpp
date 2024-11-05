#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

void solve()
{
    i64 n, m, r, c;
    cin >> n >> m >> r >> c;
    i64 ans = (m - c) + (n - r) * (m + m - 1);
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t = 1;
    cin >> t;
    while(t--) solve();
    return 0;
}