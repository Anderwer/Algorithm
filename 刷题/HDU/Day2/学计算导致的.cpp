#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int P = 1e9 + 7;

int n, m, k;

int Cal(int sum, int cur, int mul)
{
    return (sum * k + cur) * k + mul;
}

void solve()
{
    cin >> n >> m >> k;
    vector<vector<char>> a(n + 1, vector<char>(m + 1));
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++) cin >> a[i][j];

    int maxP = k * k * k;
    vector<vector<int>> tr(150, vector<int>(maxP, 0));
    for(int i = 0; i < k; i++) // sum                   包含了所有状态转移
        for(int j = 0; j < k; j++) // cur
            for(int p = 0; p < k; p++) // mul
            {
                for(char c = '0'; c <= '9'; c++) tr[c][Cal(i, j, p)] = Cal(i, (j * 10 + c - '0') % k, p);
                tr['+'][Cal(i, j, p)] = Cal((i + j * p) % k, 0, 1);
                tr['-'][Cal(i, j, p)] = Cal((i + j * p) % k, 0, k - 1);
                tr['*'][Cal(i, j, p)] = Cal(i, 0, (j * p) % k);
            }
    
    vector<vector<vector<int>>> f(n + 1, vector<vector<int>>(m + 1, vector<int>(maxP, 0)));
    f[1][1][Cal(0, (a[1][1] - '0') % k, 1)] = 1;
    
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            for(int p = 0; p < maxP; p++) //枚举状态
            {
                char now = a[i][j];
                if(now >= '0' && now <= '9') //a[i][j] 是数字
                {
                    f[i][j][tr[now][p]] = (f[i][j][tr[now][p]] + f[i][j - 1][p]) % P;
                    f[i][j][tr[now][p]] = (f[i][j][tr[now][p]] + f[i - 1][j][p]) % P;
                }
                else //a[i][j] 是运算符
                {
                    if(a[i][j - 1] >= '0' && a[i][j - 1] <= '9')
                        f[i][j][tr[now][p]] = (f[i][j][tr[now][p]] + f[i][j - 1][p]) % P;
                    if(a[i - 1][j] >= '0' && a[i - 1][j] <= '9')
                        f[i][j][tr[now][p]] = (f[i][j][tr[now][p]] + f[i - 1][j][p]) % P;
                }
            }
    
    int ans = 0;
    for(int i = 0; i < k; i++) //sum
        for(int j = 0; j < k; j++) // cur
            for(int p = 0; p < k; p++) // mul
            {
                int end = i + j * p;
                if(end % k == 0)
                    ans = (ans + f[n][m][Cal(i, j, p)]) % P;
            }
    
    cout << ans << "\n";
}

// 如果没有乘法, 就没有运算优先级, 则只用记录上一个状态的算式结果进行简单 dp
// 现在存在乘法, 想办法存储状态
// 注意到, 我们可以设 sum 表示上一个状态的算式结果, cur 表示从上一个状态读过来的数字, mul 表示从上一个状态读过来的乘法系数
// 我们发现, 无论是什么算式符号, 先更新 cur, mul 就可以把当前的结果表示成 sum + mul * cur (类似于SegmentTree 维护乘法)
// 因此, 我们要在 dp 中维护 sum, cur, mul 三个要素, 且他们均在 mod k 状态下
// 接下来考虑怎么更新 cur, sum 和 mul:

// 举例: 34 + 26 * 65 - 42
// 如果当前读入的是一个数字 x , 那么 mul = mul, sum = sum, cur = (cur * 10 + x) mod k
// 如果当前读入的是运算符 + , 那么 sum = (sum + cur * mul) mod k, mul = 1, cur = 0
// 如果当前读入的是运算符 * , 那么 sum = sum, mul = (mul * cur) mod k, cur = 0
// 如果当前读入的是运算符 - , 那么 sum = (sum + cur * mul) mod k, mul = k - 1(即 -1 mod k), cur = 0
// 由于都要 mod k, 因此 cur, sum, mul 的取值都为 [0, 20), 考虑 k 进制状态压缩存储, 上限为 k * k * k
// 设 f[i][j][p] : 到 (i, j) 时状态压缩取值为 p 时的方案数
// 状态转移:
//          如果a[i][j]是数字, 则 f[i][j][new_p] += f[i][j - 1][p]; f[i][j][new_p] += f[i - 1][j][p]
//          如果a[i][j]是运算符, 则还要先判断 a[i][j - 1] 和 a[i - 1][j] 不是运算符才能转移

// 状态压缩: 设 Cal(sum, cur, mul) = (sum * k + cur) * k + mul
// 为了快速转移, 定义 tr[当前字符][上一个状态] = 当前状态


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
