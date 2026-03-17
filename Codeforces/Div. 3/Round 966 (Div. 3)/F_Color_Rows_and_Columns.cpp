#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 1010;
int a[N], b[N];

void solve()
{
    int n, k;
    cin >> n >> k;
    for(int i = 1; i <= n; i++) cin >> a[i] >> b[i];
    vector<vector<int>> f(n + 10, vector<int>(k + 1, 1e9));
    for(int i = 0; i <= n; i++) f[i][0] = 0;

    for(int i = 1; i <= n; i++) //枚举矩形
    {
        int w = a[i], h = b[i];
        int num = a[i] + b[i];
        int cost = 0;
        for(int j = 0; j <= num; j++) //这个矩形中选了多少分
        {
            for(int x = 0; x + j <= k; x++) //0分到k分的转移
            {
                f[i + 1][x + j] = min(f[i + 1][x + j], f[i][x] + cost);
            }
            if(j == num) continue;
            if(w >= h) w--, cost += h;
            else h--, cost += w;
        }
    }
    if(f[n + 1][k] == 1e9) cout << -1 << "\n";
    else cout << f[n + 1][k] << "\n";
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

/*
对于一个会被选满的矩形来说
它给的贡献是 a + b, 它需要的操作数是 a * b

而对于最后一个被选的矩形来说, 它可以不被选满

设 f[i][j] : 前 i 个矩形, 选到 j 分的最小操作数
*/