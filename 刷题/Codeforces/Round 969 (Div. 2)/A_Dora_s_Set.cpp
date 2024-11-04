#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int l, r;
    cin >> l >> r;
    int ans = 0;
    for(int i = l + 1; i < r; i++)
    {
        if(gcd(i - 1, i + 1) == 1)
        {
            ans++;
            i += 2;
            continue;
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
/*
一个数 x 与 x - 1 互质
*/