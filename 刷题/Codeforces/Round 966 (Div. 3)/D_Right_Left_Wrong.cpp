#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 2e5 + 10;
i64 pre[N];
char s[N];

void solve()
{
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> pre[i], pre[i] += pre[i - 1];
    for(int i = 1; i <= n; i++) cin >> s[i];

    i64 ans = 0;
    int l = 1, r = n;
    while(l <= r)
    {
        if(s[l] == 'L' && s[r] == 'R')
        {
            ans += pre[r] - pre[l - 1];
            l++, r--;
        }
        while(s[l] == 'R') l++;
        while(s[r] == 'L') r--;
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
