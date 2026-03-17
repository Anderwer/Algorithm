#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int a, b;
    cin >> a >> b;
    int ans = 0;
    if(a >= b) ans = a;
    else if(b > 2 * a) ans = 0;
    else
    {
        int x = b - a;
        ans = a - x;
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
