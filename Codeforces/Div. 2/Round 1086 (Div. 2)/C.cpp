#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<long double> c(n + 1), p(n + 1), f(n + 2, 0);

    for(int i = 1; i <= n; i++)
    {
        cin >> c[i] >> p[i];
        p[i] = 1.0L - p[i] / 100.0L;
    }

    for(int i = n; i >= 1; i--)
    {
        f[i] = max(f[i + 1], c[i] + p[i] * f[i + 1]);
    }

    cout << fixed << setprecision(10) << (double)f[1] << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--)
    {
        solve();
    }
    return 0;
}
