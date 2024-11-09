#include <bits/stdc++.h>
#define int long long
using i64 = long long;
using namespace std;
const int N = 2e5 + 10;
int a[N];

void solve()
{
    int n, m, k, w;
    cin >> n >> m >> k >> w;
    for(int i = 1; i <= w; i++) cin >> a[i];

    vector<vector<int>> mp(n + 2, vector<int>(m + 2, 0)); 
    vector<vector<int>> d(n + 2, vector<int>(m + 2, 0));
    for(int i = 1; i <= n - k + 1; i++) 
    {
        for(int j = 1; j <= m - k + 1; j++) //<i, j> 是 k x k 正方形的左上角
        {
            d[i][j]++;
            d[i + k][j + k]++;
            d[i + k][j] --;
            d[i][j + k]--;
        }
    }
    map<int, int, greater<int>> cnt;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            mp[i][j] = mp[i][j - 1] + mp[i - 1][j] - mp[i - 1][j - 1] + d[i][j];
            cnt[mp[i][j]]++;
        }
    }

    sort(a + 1, a + 1 + w, greater<int>());
    i64 ans = 0;
    auto it = cnt.begin();
    for(int i = 1; i <= w; i++)
    {
        if((*it).second == 0) ++it;
        ans += a[i] * (*it).first;
        (*it).second--;
    }
    cout << ans << "\n";
    
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
