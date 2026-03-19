#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int mod = 998244353;

void solve()
{
    int n;
    cin >> n;
    vector<int> X(n + 2);
    for(int i = 1; i <= n; i++) cin >> X[i];

    for(int i = 1; i <= n; i++)
    {
        if(X[i] >= i)
        {
            cout << 0 << "\n";
            return;
        }
    }

    for(int i = 1; i <= n; i++)
    {
        if(X[i] == -1) continue;
        for(int j = 1; j < i; j++)
        {
            if(X[j] == -1) continue;
            if(X[j] < X[i] && X[i] < j && j < i)
            {
                cout << 0 << "\n";
                return;
            }
        }
    }

    function<int(int, int)> dp = [&](int l, int r) -> int
    {
        int L = r + 1;
        int ans = 1;
        vector<int> a;

        for(int i = r - 1; i > l; i--)
        {
            if(i > L) continue;
            if(X[i] != -1)
            {
                ans = 1LL * ans * dp(X[i], i) % mod;
                L = X[i];
                a.push_back(1);
            }
            else a.push_back(-1);
        }

        reverse(a.begin(), a.end());
        int m = a.size();

        vector<vector<int>> f(m + 1, vector<int>(m + 2, 0));
        vector<vector<int>> s(m + 1, vector<int>(m + 2, 0));

        f[0][1] = 1;
        s[0][0] = 0;
        s[0][1] = 1;
        for(int j = 2; j <= m + 1; j++) s[0][j] = 1;

        for(int i = 1; i <= m; i++)
        {
            for(int j = 2; j <= i + 1; j++)
            {
                if(a[i - 1] == -1)
                {
                    f[i][j] = (s[i - 1][i] - (j >= 2 ? s[i - 1][j - 2] : 0) + mod) % mod;
                }
                else
                {
                    f[i][j] = f[i - 1][j - 1];
                }
            }

            s[i][0] = f[i][0];
            for(int j = 1; j <= m + 1; j++)
            {
                s[i][j] = s[i][j - 1] + f[i][j];
                if(s[i][j] >= mod) s[i][j] -= mod;
            }
        }

        ans = 1LL * ans * s[m][m + 1] % mod;
        return ans;
    };

    cout << dp(0, n + 1) << "\n";
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
