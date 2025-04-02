#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) cin >> b[i];

    vector<int> c(n + 1);
    for(int i = 1; i <= n; i++) c[i] = a[i] + b[i];

    int ans = 0;
    if(k == 1) m += 10;
    for(int i = 1; i <= n; i++)
    {
        while(m > 0 && c[i] > 0) c[i] -= 64, m--; //模拟开枪
        if(m >= 0 && c[i] <= 0) ans++;  //如果敌人血量归零且开枪数 <= m, 则可以击杀
    }
    cout << ans << "\n";
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    solve();
    return 0;
}