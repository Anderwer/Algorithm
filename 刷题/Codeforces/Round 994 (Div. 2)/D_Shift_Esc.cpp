#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector a(n + 1, vector<int>(m + 1));
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) cin >> a[i][j];

    vector f(n + 1, vector<i64>(m + 1, 1E18 + 10));
    vector<i64> tmp(m + 1);
    for(int i = 1; i <= n; i++) //枚举行
    {
        for(i64 cnt = 0; cnt < m; cnt++) //枚举 shift 的次数
        {
            for(int j = 1; j <= m; j++)
            {
                int pos = (j + cnt) % m;
                if(pos == 0) pos = m;
                tmp[j] = a[i][pos]; //先把这一行循环位移之后的顺序存进 tmp 中
            }
            vector<i64> res(m + 1, 1E18 + 10); //存进 tmp 之后先对当前这一行进行dp
            for(int j = 1; j <= m; j++)
            {
                if(i == 1 && j == 1) res[j] = min(res[j], tmp[j]); //初始化 f[1][1]
                res[j] = min(res[j], f[i - 1][j] + tmp[j]); //从上面转移过来
                res[j] = min(res[j], res[j - 1] + tmp[j]); //从左边转移过来
                f[i][j] = min(f[i][j], res[j] + cnt * (i64)k); //加上 kx贡献
            }
        }
    }
    /*
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            cout << f[i][j] << " ";
        }
        cout << "\n";
    }
    */
   cout << f[n][m] << "\n";
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
