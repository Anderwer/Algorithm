#include <bits/stdc++.h>
#define int long long
using i64 = long long;
using namespace std;
const int N = 505;
const int p = 998244353;

int f[N][N], g[N][N];

void solve()
{
    int n, m;
    cin >> n >> m;
    f[0][0] = 1;
    for(int i = 1; i <= m; i++)
    {
        for(int j = 0; j <= i; j++)
        {
            f[i][j] = f[i - 1][j + 1] % p;
            if(j > 0) f[i][j] = (f[i][j] + f[i - 1][j - 1]) % p;
        }
    }

    for(int i = 0; i <= m; i++) g[2][i] = f[m][i];
    for(int i = 3; i <= n; i++)
    {
        for(int j = 0; j <= m; j++) //枚举万能牌数
        {
            for(int x = 0; x <= j; x++)
            {
                g[i][j] = (g[i][j] + g[i - 1][x] * f[m][j - x]) % p;
            }
        }
    }
    int ans = 0;
    if(n == 1) ans = f[m][0];
    else for(int k = 0; k <= m; k++) ans = (ans + f[m][k] * g[n][k]) % p;
    cout << ans << "\n";

}
signed main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
    return 0;
}

/*
先考虑 第一排, 第一排的牌相当于万能牌, 如果 Alice 要赢, 则 Alice 在第一排选的万能牌数要 大于等于 Bob 选的万能牌数
而在第一排中, 两人所选的牌不全都用于万能牌, 还有一部分要用于两人对抗
而两人对抗保证 Alice 赢的条件是 Alice 不存在 点数小于 Bob 的牌

我们可以把牌的点数从大到小排序, 根据 Alice 和 Bob 选了哪些牌算出选牌方案数, 这类似于长度为m的括号序列合法方案数
我们把 Alice 选的牌看作 "(", 把 Bob 选的牌看作 ")"
而括号序列的方案数即是 卡特兰数, 因此我们可以很快写出转移方程

设 f[i][j] : 前 i 次选牌, Alice 和 Bob 对抗完之后 Alice 还剩 j 张万能牌的方案数
状态转移 : f[i][j] = f[i - 1][j - 1] + f[i - 1][j + 1]
可以从 1到m 枚举 i, 再从 0到i 枚举j, 最后得到 f[m][k]
f[m][k] 的含义 : 选完了 m 张牌之后, Alice 手上还多 k 张万能牌

之后再考虑剩下的 n - 1 排, 在这 n - 1 排的选牌中, Bob 一共要多选出 k 张普通牌和 Alice 的 k 张万能牌对抗
我们假如这 k 张牌全在第 2 排选完, 则这时把 Alice 选的牌看作 ")", 把 Bob 选的牌看作 "(", 数值上等价于 f[m][k]
剩下 n - 2 排的每一排选牌方案都是 f[m][0]
因此我们要考虑如何得到总的方案数, 也可以用DP算出

设 g[i][j] : 从第 2 排到第 i 排, 一共选了 j 张多出的普通牌的方案数
状态转移 : g[i][j] = Σ g[i - 1][x] * f[m][k - x] , 其中 x ∈[0, k]
初始化 g[2][x] = f[m][x],  其中 x ∈[0, k]

最后, 由于 k 的范围是 [0, m]
ans = Σ f[m][k] * g[n][k] 
*/