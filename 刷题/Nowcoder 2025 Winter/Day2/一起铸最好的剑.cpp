#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    i64 n, m;
    cin >> n >> m;
    i64 x = m;
    int cnt = 1;
    if(m >= n)
    {
        cout << 1 << "\n";
        return;
    }
    if(m == 1)
    {
        cout << 1 << "\n";
        return;
    }
    while(m < n)
    {
        m *= x;
        cnt++;
    }
    if(m - n >= n - m / x) cnt--;
    cout << cnt << "\n";
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
