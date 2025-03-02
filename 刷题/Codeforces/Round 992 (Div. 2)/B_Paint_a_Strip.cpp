#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    int ans = 2;
    if(n == 1)
    {
        cout << 1 << "\n";
        return;
    }
    if(n <= 4)
    {
        cout << 2 << "\n";
        return;
    }
    int cnt = 4;
    while(cnt < n)
    {
        cnt = cnt * 2 + 2;
        ans++;
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

