#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    sort(a.begin() + 1, a.end(), greater<int>());
    int ans = 1E9 + 10, sum = 0;
    for(int i = 1; i <= n; i++) //枚举拿几个箱子
    {
        sum += a[i];
        if(k >= sum) ans = min(ans, k - sum);
        else break;
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
