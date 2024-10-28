#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 105;
int a[N];

void solve()
{
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    int ans = 0,mx1 = -1, mx2 = -1, sz1 = 0, sz2 = 0;
    for(int i = 1; i <= n; i += 2)
    {
        mx1 = max(mx1, a[i]);
        sz1 ++;
    }
    for(int i = 2; i <= n; i += 2)
    {
        mx2 = max(mx2, a[i]);
        sz2 ++;
    }
    ans = max(mx1 + sz1, mx2 + sz2);
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
