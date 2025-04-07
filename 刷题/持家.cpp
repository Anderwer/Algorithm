#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int P, n, k;
    cin >> P >> n >> k;
    vector<array<int, 2>> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i][0] >> a[i][1];
    
    vector<int> b1, b2;
    for(int i = 1; i <= n; i++)
    {
        if(a[i][0] == 0) b1.push_back(a[i][1]);
        else b2.push_back(a[i][1]);
    }    
    sort(b1.begin(), b1.end());
    sort(b2.begin(), b2.end(), greater<int>());

    double ans = 1e9 + 10;
    vector<double> pre1(b1.size() + 1, 1);
    vector<i64> pre2(b2.size() + 1, 0);
    for(int i = 1; i <= b1.size(); i++) pre1[i] = pre1[i - 1] * (b1[i - 1] * 0.1);
    for(int i = 1; i <= b2.size(); i++) pre2[i] = pre2[i - 1] + b2[i - 1];
    for(int x = 0; x <= k; x++)
    {
        if(x > b2.size()) break;
        int cur = P - pre2[x];
        if(cur < 0) cur = 0;
        double res = cur * pre1[k - x];
        ans = min(ans, res);
    }
    cout << ans << "\n";
    
}

// 考虑先减价钱再打折
// 设有 x 张优惠券用于降价, n - x 张用于打折
// 贪心的想, 打折券从小到大, 降价券从大到小


int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--)
    {
        solve();
    }
    return 0;
}
