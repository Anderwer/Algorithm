#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    i64 x, m;
    cin >> x >> m;
    int ans = 0;
    for(i64 i = 1; i <= x; i++) //枚举 x ^ y, 因为 x ^ y < x 
    {
        i64 y = x ^ i;
        if(y < 1 || y > m) continue;
        if(x % i == 0 || y % i == 0) ans++;
    }
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
