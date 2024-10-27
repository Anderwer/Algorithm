#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    int mx_x = 0, mx_y = 0;
    for(int i = 1; i <= n; i++)
    {
        int x, y;
        cin >> x >> y;
        mx_x = max(mx_x, x);
        mx_y = max(mx_y, y);
    }
    cout << 2 * (mx_x + mx_y) << "\n";
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
