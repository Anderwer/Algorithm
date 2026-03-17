#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 1010;
int a[N];

void solve()
{
    int n;
    cin >> n;
    int mx = -1, mn = 1e9;
    for(int i = 1; i <= n; i++) cin >> a[i], mx = max(mx, a[i]), mn = min(mn, a[i]);
    cout << (n - 1) * (mx - mn) << "\n";
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
把 a 中的最大值排第一位
把 a 中的最小值排第二位
*/