#include <bits/stdc++.h>
#define int long long
using namespace std;
using i64 = long long;

const int N = 2e5 + 10;
int a[N];

void solve()
{
    i64 n;
    i64 pre = 0, now = 0;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i], pre += a[i];
    if(n == 1 || n == 2)
    {
        cout << -1 << "\n";
        return;
    }
    sort(a + 1, a + 1 + n);
    int ans = a[n / 2 + 1] * n * 2 - pre + 1;
    cout << max(ans, 0LL) << "\n";
}

signed main() 
{
    int t = 1;
    cin >> t;
    while(t--) solve();
    return 0;
}

/*


排序 a[i]

(pre + x ) / (n * 2) == a[n / 2 + 1] + 1

pre + x == (a[n / 2 + 1] + 1) * n * 2

x == (a[n / 2 + 1] + 1) * n * 2 - pre;

*/