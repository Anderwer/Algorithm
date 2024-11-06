#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 1e5 + 10;
i64 a[N];

void solve()
{
    i64 mx = 0;
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> a[i], mx = max(mx, a[i]);

    for(int i = 1; i <= m; i++)
    {
        char x;
        int l, r;
        cin >> x >> l >> r;
        if(x == '+' && l <= mx && mx <= r) mx++;
        if(x == '-' && l <= mx && mx <= r) mx--;
        cout << mx << " ";
    }
    cout << "\n";
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
