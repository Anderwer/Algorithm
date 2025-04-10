#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<vector<int>> a(n + 1, vector<int>(k + 1, 0));
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= k; j++) 
            cin >> a[i][j];
    
    const i64 INF = -2e18;
    vector<vector<i64>> f(n + 1, vector<i64>(k + 1, INF));
    for(int j = 1; j <= k; j++)
    {
        f[1][j] = a[1][j];
        f[1][j] = max(f[1][j], f[1][j - 1]); //维护 pre max
    }

    for(int i = 2; i <= n; i++)
    {
        for(int j = 1; j <= k; j++)
        {
            f[i][j] = f[i - 1][j] + a[i][j];
        }
        for(int j = 2; j <= k; j++)
            f[i][j] = max(f[i][j], f[i][j - 1]);
    }
    cout << f[n][k] << "\n";
}

// 题中给定 n 行, 每行有 k 个数, 将序列分为 k 段
// 考虑 DP, 设 f[i][j]: 到第 i 个数为止, 当前位置 j 所能达到的最大值
// 转移: f[i][j] = max(f[i - 1]) + a[i][j]
// 因此需要维护 f[i] 的最大前缀


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
