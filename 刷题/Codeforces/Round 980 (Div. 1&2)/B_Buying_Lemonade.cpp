#include <bits/stdc++.h>
#define int long long
using i64 = long long;
using namespace std;
const int N = 2e5 + 10;

int a[N];

void solve()
{
    int n, k;
    cin >> n >> k;
    for(int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + 1 + n);
    int cnt = 0, now = 0;
    for(int i = 0; i <= n; i++)
    {
        now += (a[i + 1] - a[i]) * (n - i);
        if(now >= k)
        {
            cnt = i;
            break;
        }
    }
    cout << k + cnt << "\n";
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

*/
