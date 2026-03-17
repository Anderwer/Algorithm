#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
#define int long long

void solve()
{
    i64 n, k;
    cin >> n >> k;
    k--;
    if(n < 50 && k >= (1LL << (n - 1)))
    {
        cout << -1 << "\n";
        return;
    }

    vector<int> ans(n);
    int cnt = n - 2;
    int l = 0, r = n - 1;
    int cur = 1;
    while(cnt >= 0)
    {
        if(cnt < 50 && k >= (1LL << cnt))
        {
            ans[r--] = cur++;
            k -= (1LL << cnt);
        }
        else ans[l++] = cur++;
        cnt--;
    }
    while(cur <= n) ans[l++] = cur++;
    for(int i = 0; i < n; i++) cout << ans[i] << " ";
    cout << "\n";
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
