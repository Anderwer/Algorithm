#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
int f[105][2]; // f[i][0] : 交易了 i 次且当前手中没有股票的最大利润
               // f[i][1] : 交易了 i 次且当前手中有股票的最大利润
void solve()
{
    int n, k;
    int inf = -1e9;
    cin >> n >> k;

    for(int i = 0; i <= k; i++) f[i][1] = inf;

    for(int i = 1; i <= n; i++)
    {
        int a; cin >> a;
        for(int j = 1; j <= k; j++)
        {
            f[j][0] = max(f[j][0], f[j][1] + a); //卖出操作
            f[j][1] = max(f[j][1], f[j - 1][0] - a); //买入操作
        }
    }
    cout << f[k][0] << "\n";
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    solve();
    return 0;
}