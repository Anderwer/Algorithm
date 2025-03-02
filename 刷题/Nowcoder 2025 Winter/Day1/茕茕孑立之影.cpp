#include <bits/stdc++.h>
#define int long long
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    bool flag = true;
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i];
        if(a[i] == 1) flag = false;
    }
    if(flag == false)
    {
        cout << -1 << "\n";
        return;
    }

    i64 ans = 1e9 + 7;
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
