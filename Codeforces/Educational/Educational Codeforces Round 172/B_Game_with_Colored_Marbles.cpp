#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    vector<int> cnt(n + 1);
    for(int i = 1; i <= n; i++) cnt[a[i]]++;
    
    int x = 0, y = 0;
    for(int i = 1; i <= n; i++)
    {
        if(cnt[i] == 1) x++;
        if(cnt[i] > 1) y++;
    }
    int ans = y;
    if(x > 0) ans += ((x - 1) / 2 + 1) * 2;
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
