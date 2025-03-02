#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int m, a, b, c;
    cin >> m >> a >> b >> c;
    i64 ans = 0;
    ans += min(m, a) + min(m, b);
    int res1 = (m - a) > 0 ? m - a : 0;
    int res2 = (m - b) > 0 ? m - b : 0;
    ans += min(res1 + res2, c);
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
