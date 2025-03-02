#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    i64 n;
    cin >> n;
    vector<int> a(n + 1);
    i64 sum = 0;
    for(int i = 1; i <= n; i++) cin >> a[i], sum += a[i];

    sort(a.begin() + 1, a.end());
    int ans = 0;
    for(int i = 1; i <= n; i++)
    {
        ans += abs(i - a[i]);
    }
    if(n * (n + 1) / 2 != sum) cout << -1 << "\n";
    else cout << ans / 2 << "\n";
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
