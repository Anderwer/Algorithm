#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> g(n, vector<int>(n));
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++) cin >> g[i][j];
    }

    vector<vector<int>> f(1 << n, vector<int>(n, 1E9 + 10)); //f[1 << i][i] 从 i 出发, 状态变为 1 << i
    //for(int i = 0; i < n; i++) f[1 << i][i] = 0; //初始化dp
    f[1 << 0][0] = 0;
    for(int i = 0; i < (1 << n); i++) //枚举状态
    {
        for(int j = 0; j < n; j++) //枚举出发点
        {
            if((i >> j) & 1 == 0) continue; //如果出发点没走过, 说明还不能走
            for(int k = 0; k < n; k++) //枚举下一个到的点
            {
                if((i >> k) & 1 == 1) continue; //如果下一个到达的点走过, 说明不用走了
                f[i | (1 << k)][k] = min(f[i | (1 << k)][k], f[i][j] + g[j][k]);
            }
        }
    } 

    int ans = 1E9 + 10;
    for(int i = 1; i < n; i++)
    {
        ans = min(ans, f[(1 << n) - 1][i] + g[i][0]); // (1 << n) - 1 刚好凑齐满 '1'二进制位
    }
    cout << ans << "\n";
}

int main()
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
