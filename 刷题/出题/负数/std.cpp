#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);

    for(int i = 1; i <= n; i++) cin >> a[i];
    map<int, int> cnt;
    for(int i = 1; i <= n; i++) cnt[abs(a[i])]++;

    int ans = 0;
    for(auto [x, y] : cnt) ans += min(2, y);
    if(cnt[0] > 1) ans--;
    cout << ans << "\n";
}

int main()
{
    //std::ios::sync_with_stdio(false);
    //std::cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
