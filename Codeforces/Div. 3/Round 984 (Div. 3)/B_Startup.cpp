#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int N = 2e5 + 10;
int b[N], c[N];

void solve()
{
    int n, k;
    cin >> n >> k;
    for(int i = 1; i <= k; i++) cin >> b[i] >> c[i];
    map<int, int> mp;
    for(int i = 1; i <= k; i++) mp[b[i]] += c[i];
    vector<int> sum;
    for(auto& [x, y] : mp) sum.push_back(y);
    sort(sum.begin(), sum.end(), greater<int>());
    int cnt = 0;
    i64 ans = 0;
    for(auto v : sum)
    {
        if(cnt < n) cnt++, ans += v;
        else break;
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