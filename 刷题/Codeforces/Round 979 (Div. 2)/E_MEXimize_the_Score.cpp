#include <bits/stdc++.h>
#define int long long
using i64 = long long;
using namespace std;
const int N = 2e5 + 10;
const int p = 998244353;
int a[N];
int cnt[N], fact[N + 1], infact[N + 1];
int g[2][N], f[2][N], top[2];

void init(int n)
{
    top[0] = top[1] = 0;
    for(int i = 0; i <= n; i++) cnt[i] = g[0][i] = g[1][i] = f[0][i] = f[1][i] = 0;
}

int qpow(int a, int b)
{
    int res = 1;
    while(b)
    {
        if(b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res % p;
}

void IComb()
{
    fact[0] = 1;
    for(int i = 1; i <= N; i++) fact[i] = (fact[i - 1] * i) % p;
    infact[N] = qpow(fact[N], p - 2);
    for(int i = N - 1; i >= 0; i--) infact[i] = (infact[i + 1] * (i + 1)) % p;
}

int C(int a, int b)
{
    if(b > a || b < 0) return 0;
    return (fact[a] * ((infact[b] * infact[a - b]) % p)) % p;
}



void solve()
{
    int n;
    cin >> n;
    init(n);
    for(int i = 1; i <= n; i++) cin >> a[i], cnt[a[i]]++;
    for(int i = 1; i <= cnt[0]; i++) //处理 i = 0 的时候
    {
        f[0][i] = C(cnt[0], i) * i % p;
        g[0][i] = C(cnt[0], i) % p;
    }
    
    top[0] = cnt[0];
    int pos = 0;
    for(int i = 1; i <= n; i++) //从 i = 1 开始递推
    {
        int sum_c = qpow(2, cnt[i]);
        int tail_f = 0, tail_g = 0; //统计后缀和
        for(int j = 0; j <= top[pos]; j++)
        {
            tail_f = (tail_f + f[pos][j]) % p;
            tail_g = (tail_g + g[pos][j]) % p;
        }
        top[1 - pos] = min(cnt[i], top[pos]); 

        for(int j = 0; j <= top[1 - pos]; j++)
        {
            int Cij = C(cnt[i], j);
            tail_f = ((tail_f - f[pos][j]) % p + p) % p;
            tail_g = ((tail_g - g[pos][j]) % p + p) % p;

            g[1 - pos][j] = ((g[pos][j] % p * sum_c % p) % p + (tail_g % p * Cij % p) + p) % p;

            f[1 - pos][j] = ((f[pos][j] % p * sum_c % p) % p + (tail_f % p * Cij % p) % p + (g[pos][j] % p * sum_c % p * j % p) % p + (tail_g % p * Cij % p * j % p) % p + p) % p;

            sum_c = ((sum_c - Cij) % p + p) % p;
        }
        pos = 1 - pos;
    }
    cout << f[pos][0] << "\n";
}
signed main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    cin >> t;
    IComb();
    while(t--){
        solve();
    }
    return 0;
}

/*
一个数组要分成若干个集合, 求所有集合的 MEX 之和, 贪心的想, 如果两个相同的数出现在同一个集合里, 则必有一个数没有意义
因此, 我们要尽量在每个集合里放不同的数, 且要从小到大放
假设数组 a = [0, 0, 0, 0, 1, 1, 1, 2, 2, 3, 4], 那么集合应该如下分布:

0           ---- Mex = 1
0 1         ---- Mex = 2
0 1 2       ---- Mex = 3
0 1 2 3 4   ---- Mex = 4
我们可以分成 4 个集合, 这样能保证 Mex 之和最大

设 f[i][j] : 从 0到i, 当前摆了 j 个 i 构成的最大 Mex 之和

0
0 1
0 1
0 1 2     假设我们已经算出了 f[1][3] 现在要算 f[2][0], 显然 f[2][0] = f[1][3]
当我们在 '2' 这一列放上一个 2 时, 这时候要计算 f[2][1], 假设原数组里面有3个 '2', 那么我们要从3个里面选一个, 则 f[2][1] = f[1][2] * C[3][1]
且放完这个 '2'之后, 我们发现拼了 '2' 的这一个集合的 Mex 发生了变动, 因此我们还要知道一共有多少个集合能够拼 '2'
设 g[i][j] : 从 0到i, 当前摆了 j 个 i 构成的 从 0到i 的集合数量
则 f[2][1] 还要加上 g[1][2] * C[3][1], 这是计算有多少个集合会因为拼接了一个 '2' 而导致Mex变动

现在来研究一下 g[i][j] 该怎么推

0
0 1
0 1
0 1 2
假如我们已经算出了 g[1][3], 现在要算 g[2][1], 且数组中有 3 个 '2'
显然 g[2][1] = g[1][1] * C[3][1]
             + g[1][2] * C[3][1]
             + g[1][3] * C[3][1]
             ...
             + g[1][Top[1]] * C[3][1] 
             ----------------------------- 上面是取 1 个 '2'的情况, 如果我们一次性拼上去很多个 '2', 但是固定住左边的高度, g[2][1] 也是有变化的
             + g[1][1] * C[3][2]
             + g[1][1] * C[3][3]

因此, 我们可以推出 g[i][j] 的转移:
    g[i][j] = g[i - 1][j] * C[cnt[i]][j]
            + g[i - 1][j + 1] * C[cnt[i]][j]
            + g[i - 1][j + 2] * C[cnt[i]][j]
            + ...
            + g[i - 1][Top[i - 1]] * C[cnt[i]][j]
            -------------------------------------------
            + g[i - 1][j] * C[cnt[i]][j + 1]
            + g[i - 1][j] * C[cnt[i]][j + 2]
            + ...
            + g[i - 1][j] * C[cnt[i]][cnt[i]]
我们发现, 上半部分的 C[cnt[i]][j] 不变, 下半部分的 g[i - 1][j] 不变, 因此
我们只需要得到 g[i - 1] 的后缀和, 以及 C[cnt[i]]的后缀和就能 O(1) 算出g[i][j]
由于 g[i][j] 只与 g[i - 1]有关, 因此我们可以用滚动优化空间复杂度

*/