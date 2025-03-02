#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
int vis[10010];

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    int ans = 0, sum = 0;
    for(int i = 1; i <= n; i++)
    {
        sum += a[i];
        if(vis[sum] == true) ans++;
    }
    cout << ans << "\n";
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    cin >> t;
    for(int i = 1; i * i <= 10005; i += 2) vis[i * i] = true; 
    while(t--){
        solve();
    }
    return 0;
}
