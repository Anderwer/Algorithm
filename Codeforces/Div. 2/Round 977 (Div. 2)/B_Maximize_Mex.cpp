#include <bits/stdc++.h>
using i64 = long long;
using namespace std;


void solve()
{
    int n, x;
    cin >> n >> x;
    vector<int> a(n), cnt(n + 1, 0);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++)
    {
        if(a[i] >= n) continue;
        cnt[a[i]]++;
    }
    int ans = 0;
    while(ans < n && cnt[ans] > 0)
    {
        if(cnt[ans] > 1 && ans + x < n)
        {
            cnt[ans + x] += (cnt[ans] - 1);
            cnt[ans] = 1;
        }
        ans++;
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
