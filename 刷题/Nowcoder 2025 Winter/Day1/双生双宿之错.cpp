#include <bits/stdc++.h>
#define int long long
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    sort(a.begin() + 1, a.end());
    int x, y; //左半边和右半边的中位数
    if((n / 2) % 2 == 0)
    {
        int k = n / 2;
        x = (a[k / 2] + a[k / 2 + 1]) / 2;
        y = (a[k / 2 + k] + a[k / 2 + k + 1]) / 2;
    }
    else
    {
        int k = n / 2;
        x = a[k / 2 + 1];
        y = a[k / 2 + k + 1];
    }

    int res1 = 0, res2 = 0;
    for(int i = 1; i <= n / 2; i++) res1 += abs(a[i] - x);
    for(int i = n / 2 + 1; i <= n; i++) res2 += abs(a[i] - y);
    if(x == y) //特判两边中位数相等的情况
    {
        int resLeft = 0, resRight = 0;
        x--, y++;
        for(int i = 1; i <= n / 2; i++) resLeft += abs(a[i] - x);
        for(int i = n / 2 + 1; i <= n; i++) resRight += abs(a[i] - y);
        cout << min(resLeft + res2, resRight + res1) << "\n";
    }
    else cout << res1 + res2 << "\n";
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
