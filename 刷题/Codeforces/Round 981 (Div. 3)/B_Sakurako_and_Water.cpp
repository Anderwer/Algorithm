#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 505;
int mp[N][N];

void solve()
{
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) cin >> mp[i][j];
    int ans = 0;
    map<int, int> cnt;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            cnt[j - i] = min(cnt[j - i], mp[i][j]);
        }
    }
    for(auto [x, y] : cnt) ans += y;
    cout << -ans << "\n";
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
