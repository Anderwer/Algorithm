#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
int vis[10];

void solve()
{
    int a, b;
    cin >> a >> b;
    vis[a] = vis[b] = 1;
    int ans = 0;
    for(int i = 1; i <= 3; i++) if(vis[i] == 0) ans = i;    
    cout << ans << "\n";
}
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
