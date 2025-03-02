#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    vector<int> pre_max(n + 2, 0), suf_min(n + 2, 1E9);
    for(int i = 1; i <= n; i++) pre_max[i] = max(a[i], pre_max[i - 1]);
    for(int i = n; i >= 1; i--) suf_min[i] = min(a[i], suf_min[i + 1]);

    vector<int> ans(n + 1);
    ans[n] = pre_max[n];
    for(int i = n - 1; i >= 1; i--)
    {
        if(pre_max[i] > suf_min[i + 1]) ans[i] = ans[i + 1];
        else ans[i] = pre_max[i];
    }
    for(int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << "\n";
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
