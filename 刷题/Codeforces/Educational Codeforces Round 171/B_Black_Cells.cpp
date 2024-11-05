#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

i64 check(vector<i64>& a, int i, int flag)
{
    i64 res = -1;
    vector<i64> now = a;
    now.push_back(a[i] + flag);
    sort(now.begin(), now.end());
    for(int j = 0; j < now.size(); j+=2) res = max(res, now[j + 1] - now[j]);
    return res;
}

void solve()
{
    int n;
    cin >> n;
    vector<i64> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    
    i64 ans = 1e18;
    if(n & 1)
    {
        for(int i = 0; i < n; i++) //枚举第 i 个位置的 左边和右边 涂成黑块
        {
            ans = min({ans, check(a, i, -1), check(a, i, 1)});
        }
    }
    else
    {
        i64 res = -1;
        for(int i = 0; i < n; i+=2) res = max(res, a[i + 1] - a[i]);
        ans = res;
    }
    cout << ans << '\n';
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
/*
a 数组有序

*/