#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 1e5 + 10;
int a[N];
i64 pre[N];

void solve()
{
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i], pre[i] = pre[i - 1] + a[i];

    int ans = 0, now_pos = 0;
    map<i64, i64> pos;
    pos[0] = 0;
    for(int i = 1; i <= n; i++)
    {   
        if(pos.count(pre[i]) && pos[pre[i]] >= now_pos)
        {
            ans++;
            now_pos = i;
        }
        pos[pre[i]] = i;
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
