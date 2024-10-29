#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n, x, y;
    cin >> n >> x >> y;
    cout << (n + min(x, y) - 1) / min(x, y) << '\n';
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
