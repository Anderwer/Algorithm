#include <bits/stdc++.h>
#define int long long
using namespace std;
using i64 = long long;

void solve()
{
    int x, y, z, k;
    cin >> x >> y >> z >> k;

    int ans = 1e18;
    for(int a = 0; a <= 1e8; a++)
    {
        int A = z - (k * a + k) * a / 2;
        if(A < 0) break;
        int nxt = 0;
        for(int ka_b = max(1LL, k * a); ka_b <= min(A, k * a + k); ka_b = nxt + 1)
        {
            if(ka_b == A) nxt = A;
            else nxt = (A - 1) / ((A - 1) / ka_b);
            ans = min(ans, a * (k * x + y) + (ka_b - k * a) * x + ((A + ka_b - 1) / ka_b) * y);
        }
    }
    cout << ans << "\n";
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t = 1;
    cin >> t;
    while(t--) solve();
    return 0;
}