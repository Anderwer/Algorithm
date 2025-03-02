#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    i64 k, l1, r1, l2, r2;
    cin >> k >> l1 >> r1 >> l2 >> r2;

    i64 ans = 0, kn = 1;
    for(int n = 0; n <= 31; n++)
    {
        if(n > 0) kn *= k;
        if(kn > r2) break;
        i64 res = min(r1, r2 / kn) - max(l1, (l2 - 1) / kn + 1) + 1;
        if(res > 0) ans += res;
    }
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
