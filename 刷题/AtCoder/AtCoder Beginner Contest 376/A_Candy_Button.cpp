#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n, c;
    cin >> n >> c;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    int ans = 0, now = 0;
    for(int i = 1; i <= n; i++)
    {
        if(i == 1)
        {
            now = a[i];
            ans++;
            continue;
        }
        if(a[i] - now >= c) ans++, now = a[i];
    }
    cout << ans << "\n";
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
