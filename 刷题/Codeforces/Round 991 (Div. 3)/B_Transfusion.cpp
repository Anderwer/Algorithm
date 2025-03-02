#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    i64 sum = 0;
    for(int i = 1; i <= n; i++) sum += a[i];
    if(sum % n != 0)
    {
        cout << "NO\n";
        return;
    }

    i64 all = sum / n;
    i64 last1 = 0, last2 = 0;
    for(int i = 1; i <= n; i += 2)
    {   
        if(a[i] > all) last1 += (a[i] - all);
        if(a[i] < all) last1 -= (all - a[i]);
    }
    for(int i = 2; i <= n; i += 2)
    {
        if(a[i] > all) last2 += (a[i] - all);
        if(a[i] < all) last2 -= (all - a[i]);
    }
    if(last1 == 0 && last2 == 0) cout << "YES\n";
    else cout << "NO\n";
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
