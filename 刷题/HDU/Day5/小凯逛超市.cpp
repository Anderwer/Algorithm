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
        for(int k = g[i]; k <= V; k++)
        {
            for(int j = 1; j <= m; j++)
            {
                f[j][k] = (f[j][k] + f[j - 1][k - g[i]]) % p;
            }
        }
    }
    
    int ans = 0;
    for(int i = 0; i <= V; i++) ans = (ans + f[m][i]) % p;
    cout << ans << "\n";
}

// 设 f[i][j][k]: 到前 i 种物品, 体积为 j, 花费为 k 时的方案数
// 状态转移: f[i][j][k] += f[i - 1][j - x][k - x * g[i]] 其中 x <= min(j, k / g[i])
// 观察转移方程, 发现 f[i] 只与 f[i - 1] 有关, 因此可以滚动优化掉第一维
// 则转移变为: f[j][k] += f[j - x][k - x * g[i]]

// 考虑正向枚举, 外层枚举花费 k, 内层枚举体积 j
// 则有 f[j][k] += f[j - 1][k - g[i]]
// 这种枚举方法下, 对于同一个 k, 所有 j 的状态都被更新了, 可以抽象为在花费一定的情况下, 买了多个同种物品

// 如果是外层枚举体积 j, 内层枚举花费 k, 则对于同一个 j, 所有 k 的状态都被更新了
// 但是由于上一个状态全是 j - 1 来的, 可以抽象为每种物品只买了一个, 与题意不符

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
