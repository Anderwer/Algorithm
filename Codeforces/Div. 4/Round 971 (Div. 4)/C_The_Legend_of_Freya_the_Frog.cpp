#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int x, y, k;
    cin >> x >> y >> k;
    int cnt_1 = x / k;
    if(x % k) cnt_1++;
    int cnt_2 = y / k;
    if(y % k) cnt_2++;
    int ans = max(cnt_1, cnt_2) * 2;
    if(cnt_1 > cnt_2) ans--;
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
/*
跳 20000步到(100000, 100000)
此时该往x跳, x还剩9900000

*/