#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int N = 4e5 + 10;
char s[N];
i64 pre[N];

void solve()
{
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> s[i], pre[i] = pre[i - 1] + i;
    int now = 0;
    i64 ans = 0;
    for(int i = 1; i <= n; i++)
    {
        if(s[i] == '0') continue;
        if(s[i + 1] == '1') continue;
        ans += pre[i] - pre[now] - i;
        now = i;
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t = 1;
    cin >> t;
    while(t--) solve();
    return 0;
}