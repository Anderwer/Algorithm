#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int p = 1e9 + 7;

void solve()
{
    int n, m, V;
    cin >> n >> m >> V;
    vector<int> g(n + 1);
    for(int i = 1; i <= n; i++) cin >> g[i];

    vector<vector<int>> f(m + 1, vector<int>(V + 1, 0));
    f[0][0] = 1;
    for(int i = 1; i <= n; i++)
    {
        if(V - g[i] < 0) continue;
        for(int k = 0; k < m; k++)
        {
            for(int c = 0; c <= V - g[i]; c++)
            {
                if(f[k][c] == 0) continue;
                f[k + 1][c + g[i]] = (f[k + 1][c + g[i]] + f[k][c]) % p;
            }
        }
    }

    int ans = 0;
    for(int i = 0; i <= V; i++) ans = (ans + f[m][i]) % p;
    cout << ans << "\n"; 
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--)
    {
        solve();
    }
    return 0;
}
