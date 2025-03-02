#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    string a;
    string b;
    string c;
    cin >> a >> b >> c;

    int n = a.size();
    int m = b.size();
    vector<vector<int>> f(n + 1, vector<int>(m + 1, -1)); //f[i][j] : a 中选了[0 ~ i], b中选了[0 ~ j]构成的字符串和 c中前[0 ~ i + j]一样的数量
    f[0][0] = 0;
    for(int i = 0; i <= n; i++)
    {
        for(int j = 0; j <= m; j++)
        {
            if(f[i][j] == -1) continue;
            if(i < n) f[i + 1][j] = max(f[i + 1][j], f[i][j] + (a[i] == c[i + j] ? 1 : 0));
            if(j < m) f[i][j + 1] = max(f[i][j + 1], f[i][j] + (b[j] == c[i + j] ? 1 : 0));
        }
    }
    cout << n + m - f[n][m] << "\n";
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
