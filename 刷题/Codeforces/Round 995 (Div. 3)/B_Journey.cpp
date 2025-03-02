#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n, a, b, c;
    cin >> n >> a >> b >> c;
    int x = n % (a + b + c);
    int ans = (n / (a + b + c)) * 3;
    if(x > 0) ans++, x -= a;
    if(x > 0) ans++, x -= b;
    if(x > 0) ans++, x -= c;
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
