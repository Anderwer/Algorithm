#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    string a, b;
    cin >> a >> b;
    int cnt = 0;
    int len = min((int)a.size(), (int)b.size());
    for(int i = 0; i < len; i++)
    {
        if(a[i] == b[i]) cnt++;
        else break;
    }
    int ans = 0;
    if(cnt > 0) ans = cnt + 1;
    ans += a.size() + b.size() - cnt * 2;
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
