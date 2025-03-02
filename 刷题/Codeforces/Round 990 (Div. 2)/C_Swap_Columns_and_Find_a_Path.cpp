#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) cin >> b[i];

    int ans = -1E9;
    for(int i = 1; i <= n; i++) //枚举第 i 往下走
    {
        int res = a[i] + b[i];
        for(int j = 1; j <= n; j++)
        {
            if(i == j) continue;
            res += max(a[j], b[j]);
        }
        ans = max(ans, res);
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
