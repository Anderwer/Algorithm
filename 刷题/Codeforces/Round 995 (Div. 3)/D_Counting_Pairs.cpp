#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    i64 n, x, y;
    cin >> n >> x >> y;
    vector<int> a(n + 1);
    a[0] = 0;
    for(int i = 1; i <= n; i++) cin >> a[i];

    i64 sum = 0;
    for(int i = 1; i <= n; i++) sum += a[i];

    sort(a.begin(), a.end());
    i64 ans = 0;
    for(int i = 1; i < n; i++)
    {
        int Lpos = lower_bound(a.begin(), a.end(), sum - y - a[i]) - a.begin();
        int Rpos = upper_bound(a.begin(), a.end(), sum - x - a[i]) - a.begin();
        //cout << Lpos << " " << Rpos << "\n";
        if((Rpos - max(Lpos, i)) > 0)
        {
            if(max(Lpos, i) == i) ans += (Rpos - max(Lpos, i)) - 1;
            else ans += (Rpos - max(Lpos, i));
        }
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
