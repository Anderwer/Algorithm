#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

i64 pow2(i64 x)
{
    return x * x;
}

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<i64> c(n + 1), a(m + 1);
    for(int i = 1; i <= n; i++) cin >> c[i];
    for(int i = 1; i <= m; i++) cin >> a[i];

    vector<array<i64, 2>> b(n + 1);
    for(int i = 1; i <= n; i++) b[i][0] = c[i];
    for(int i = 1; i <= m; i++) b[a[i]][1] = 1;
    sort(b.begin() + 1, b.end());

    const i64 INF = 2e18;
    vector<array<i64, 2>> f(n + 1, {INF, INF});
    f[1][0] = 0;
    f[2][1] = pow2(b[2][0] - b[1][0]);
    if(b[1][1] == 0) f[2][0] = 0;

    for(int i = 3; i <= n; i++)
    {
        if(b[i - 1][1] == 1) // 第 i - 1 根为必选
        {
            f[i][0] = min(f[i][0], f[i - 1][1]);
            f[i][1] = min(f[i][1], f[i - 1][0] + pow2(b[i][0] - b[i - 1][0]));
        }
        else
        {
            f[i][0] = min({f[i][0], f[i - 1][0], f[i - 1][1]});
            f[i][1] = min({f[i][1], f[i - 1][0] + pow2(b[i][0] - b[i - 1][0]), f[i - 2][0] + pow2(b[i][0] - b[i - 2][0])});
        }
    }

    i64 ans = INF;
    if(b[n][1] == 1) ans = min(ans, f[n][1]);
    else ans = min(f[n][0], f[n][1]);
    cout << ans << "\n";
}

// 首先, 看到 (a - b)^2 最小, 则应该对数组进行排序
// 转化成有序序列后, 从中选择 m + x 根筷子, 使得不舒适度的和最小
// 假设有 a <= b <= c <= d, 如果 a 和 c 是必选的, 则一共有三种选法:
// 1. 选择 (a, b) 和 (c, d)
// 2. 选择 (a, d) 和 (b, c)
// 3. 选择 (a, c)

// 对选法 1 来说, 它的不舒适度为 (a - b) * (a - b) + (c - d) * (c - d) = a^2 + b^2 + c^2 + d^2 - 2(ab + cd)
// 对选法 2 来说, 它的不舒适度为 (a - d) * (a - d) + (b - c) * (b - c) = a^2 + b^2 + c^2 + d^2 - 2(ad + bc)
// 因此比较 (ab + cd) 和 (ad + bc) 即可, 假设 ad + bc <= ab + cd, 移项得 a(d - b) + c(b - d) <= 0 ----> a(d - b) <= c(d - b) ----> a <= c, 假设成立 
// 所以有 ad + bc <= ab + cd, 则选法 1 更优, 但是选法 1 和选法 3 无法判断
// 综上, 我们有两个决策, 当某个筷子必选时, 和它配对的要么是相邻的筷子, 要么是相隔了一个筷子再选(因为不知道选法 1 和选法 3 谁更优)
// 因此, 考虑DP

// 设 f[i][0] : 前 i - 1 根筷子中所有必选的都选了, 当前第 i 根不选的最优解
// 设 f[i][1] : 前 i - 1 根筷子中所有必选的都选了, 当前第 i 根选的最优解

// 则有转移:
// 如果第 i - 1 根为必选, 则有 f[i][0] = f[i - 1][1], f[i][1] = f[i - 1][0] + (a[i] - a[i - 1])^2
// 如果第 i - 1 根非必选, 则有 f[i][0] = min(f[i - 1][0], f[i - 1][1]), f[i][1] = min(f[i - 1][0] + (a[i] - a[i - 1])^2, f[i - 2][0] + (a[i] - a[i - 2])^2)

// 观察转移方程, 对 DP 进行初始化:
// 初始下所有 f[i][0/1] 都为 INF
// f[1][0] = 0, f[1][1] = INF (因为第一根筷子不能单选)
// f[2][1] = (a[2] - a[1])^2
// 如果第一根筷子非必选, 则 f[2][0] = 0 (因为如果第一根筷子必选的话, f[2][0] 不合法)

// 最后, 如果最后一根为必选, 则 ans = f[n][1]
// 否则 ans = min(f[n][0], f[n][1])

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
