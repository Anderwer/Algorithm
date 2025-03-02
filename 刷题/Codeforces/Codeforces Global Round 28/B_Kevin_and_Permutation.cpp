#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> ans(n + 1, 0);
    
    int now = 0;
    for(int i = k; i <= n; i += k) ans[i] = ++now;
    for(int i = 1; i <= n; i++)
    {
        if(ans[i] == 0) ans[i] = ++now;
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
