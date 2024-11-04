#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n, q;
    cin >> n >> q;
    int l_pos = 1, r_pos = 2;
    int ans = 0;
    while(q --)
    {
        char H;
        int T;
        cin >> H >> T;
        if(H == 'R')
        {
            if(T == r_pos) continue;
            if(min(T, r_pos) < l_pos && l_pos < max(T, r_pos)) ans += (n - max(T, r_pos) + min(T, r_pos));
            else ans += max(T, r_pos) - min(T, r_pos);
            r_pos = T;
        }
        else
        {
            if(T == l_pos) continue;
            if(min(T, l_pos) < r_pos && r_pos < max(T, l_pos)) ans += (n - max(T, l_pos) + min(T, l_pos));
            else ans += max(T, l_pos) - min(T, l_pos);
            l_pos = T;
        }
    }
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
/*
如果 H = 'R', 则要让 r_pos 移动到 T 的位置, 可以向左或者向右

*/