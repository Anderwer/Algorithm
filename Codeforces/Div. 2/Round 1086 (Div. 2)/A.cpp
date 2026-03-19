#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<int> cnt(n * n + 1, 0);

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            int x;
            cin >> x;
            cnt[x]++;
        }
    }

    int mx = 0;
    for(int i = 1; i <= n * n; i++) mx = max(mx, cnt[i]);

    if(mx <= n * (n - 1)) cout << "YES\n";
    else cout << "NO\n";
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
