#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> a(q);
    vector<char> c(q);
    for(int i = 0; i < q; i++) cin >> a[i] >> c[i], a[i]--;

    vector g(n, vector<int>(n, 0));
    for(int i = 0; i < n; i++) //统计从 i 到 j 之间的最短距离
    {
        for(int j = 0; j < n; j++)
        {
            if(i == j) continue;
            int dist = 1, res = 1;
            for(int k = 0; k < q; k++)
            {
                if(a[k] == i)
                {
                    if(c[k] == '+') dist--;
                    if(dist == 0) res++, dist++;
                }
                if(a[k] == j)
                {
                    if(c[k] == '-') dist++;
                }
            }
            g[i][j] = res;
        }
    }

    vector<int> cnt(n, 0); //统计每个点有过多少个 '+'
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < q; j++)
        {
            if(a[j] == i && c[j] == '+') cnt[i]++;
        }
    }

    vector f(1 << n, vector<int>(n, 1E9 + 10));
    for(int i = 0; i < n; i++) f[1 << i][i] = 1; //初始化 从点 i 作为起点的值为 1
    for(int i = 0; i < (1 << n); i++) //枚举所有状态
    {
        for(int j = 0; j < n; j++) //枚举所有状态
        {
            if((i >> j & 1) == 0) continue; //说明村庄 j 没走过
            for(int k = 0; k < n; k++) //枚举接下来可以走的村庄
            {
                if((i >> k & 1) == 0) f[i | (1 << k)][k] = min(f[i | (1 << k)][k], f[i][j] + g[j][k]); //状态转移, 从当前状态 i ∪ k
            } 
        }
    }
    int ans = 1E9 + 10;
    for(int i = 0; i < n; i++) ans = min(ans, f[(1 << n) - 1][i] + cnt[i]);
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
