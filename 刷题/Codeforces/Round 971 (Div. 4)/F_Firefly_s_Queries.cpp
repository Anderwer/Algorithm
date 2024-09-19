#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

const int N = 2e5 + 10;
int a[N];
i64 pre[N];
int n, q;

i64 cal(i64 x)
{
    i64 times = x / n;
    i64 pos = x % n + times;
    i64 cnt = pre[n] * times;
    if(pos <= n)
    {
        cnt += pre[pos] - pre[times];
    }
    else cnt += pre[pos - n] + pre[n] - pre[times];
    return cnt;
}

void solve()
{
    cin >> n >> q;
    pre[0] = 0;
    for(int i = 1; i <= n; i++) cin >> a[i], pre[i] = pre[i - 1] + a[i];

    while(q--)
    {
        i64 l, r;
        cin >> l >> r;
        i64 ans = cal(r) - cal(l - 1);
        cout << ans << "\n";
    }
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
