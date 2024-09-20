#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

const int N = 50010;
int a[N];

void solve()
{
    int l, r;
    cin >> l >> r;
    int x = r - l;
    int ans = lower_bound(a + 1, a + 1 + 50000, x) - a;
    if(x < a[ans]) ans--;
    cout << ans << "\n";
}
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    cin >> t;
    int cnt = 1;
    for(int i = 2; i < 50000; i++)
    {
        a[i] = a[i - 1] + cnt;
        cnt++;
    }
    while(t--){
        solve();
    }
    return 0;
}
