#include <bits/stdc++.h>
#define int long long
using i64 = long long;
using namespace std;
const int N = 2e5 + 10;
bool vis[N];

void solve()
{
    int n, m, mx = 0;
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
    {
        int l; cin >> l;
        for(int j = 0; j <= l + 10; j++) vis[j] = false;
        for(int j = 1; j <= l; j++)
        {
            int x; cin >> x;
            if(x <= l + 1) vis[x] = true;
        }
        int now = 0;
        while(vis[now]) now++;
        vis[now] = 1;
        while(vis[now]) now++;
        mx = max(mx, now);
    }
    if(mx >= m) cout << (m + 1) * mx << "\n";
    else cout << mx * mx + (m + mx) * (m - mx + 1) / 2 << "\n";

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

/*
如果 一个 k 比通过操作能变到的数更大, 那么它就不进行操作
现在可以对每一行找第一个 Mex_1 和第二个 Mex_2
如果 x = Mex_1, 那么它可以 x -> Mex_2
否则, x -> Mex_1

*/