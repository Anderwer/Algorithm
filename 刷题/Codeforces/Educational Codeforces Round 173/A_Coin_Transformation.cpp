#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    i64 n;
    cin >> n;
    i64 ans = 1;
    while(n > 3)
    {
        ans *= 2;
        n /= 4;
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
