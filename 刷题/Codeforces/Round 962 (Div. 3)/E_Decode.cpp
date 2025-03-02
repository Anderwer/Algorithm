#include <bits/stdc++.h>
#define int long long
using i64 = long long;
using namespace std;
const int p = 1e9 + 7;

void solve()
{
    string s;
    cin >> s;
    s = " " + s;
    int n = s.size() - 1;
    vector<int> pre(n + 1, 0);
    for(int i = 1; i <= n; i++)
    {
        if(s[i] == '1') pre[i] = pre[i - 1] + 1;
        else pre[i] = pre[i - 1] - 1;
    }

    i64 ans = 0;
    map<int, int> pos; //记录当前的前缀和的定位
    pos[0] = 1;
    for(int i = 1; i <= n; i++)
    {
        ans += pos[pre[i]] * (n - i + 1);
        ans = ans % p;
        pos[pre[i]] += i + 1;
    }
    cout << ans << '\n';
}

signed main()
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
