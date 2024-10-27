#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 1010;

int a[N];

void solve()
{
    int n, r;
    cin >> n >> r;
    for(int i = 1; i <= n; i++) cin >> a[i];
    int ans = 0, cnt = 0, num = 0;
    for(int i = 1; i <= n; i++)
    {
        if(a[i] < 2) continue;
        ans += (a[i] / 2) * 2;
        cnt += (a[i] / 2);
        a[i] %= 2;
    }
    for(int i = 1; i <= n; i++) if(a[i] == 1) num++;
    if(num <= r - cnt) ans += num;
    else ans += 2 * (r - cnt) - num;
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
