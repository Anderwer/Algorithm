#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 105;
const int p = 1e9 + 7;
int dp[N][N];

int f(int x, int y)
{
    if(x == 0) return 1;
    if(dp[x][y]) return dp[x][y] % p;
    for(int i = 1; i <= y; i++)
        if(x - i >= 0) dp[x][y] = (dp[x][y] + f(x - i, y)) % p;
    return dp[x][y] % p;
}

void solve()
{
    int n, k, d;
    cin >> n >> k >> d;
    cout << (f(n, k) - f(n, d - 1) + p) % p << "\n"; 
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
/*
我们可以用一个函数 f(n, k) 表示 用边权为1 ~ k 的边加到 边权总和为 n 的方案数
又因为题目条件需要至少一条边的边权 >= k
因此 ans = f(n, k) - f(n, d - 1)
求 f(n, k) 可以用 记忆化dp
设 dp[i][j] : 用边权为 1 ~ k 的边加到 边权总和为 i 的方案数

状态转移: dp[i][j] += dp[i - x][j], 其中 x 从 1 到 j
*/