#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void dfs(int u, int fa, int GCD, int& cnt, vector<vector<int>>& g, vector<int>& a)
{
    if(u != 1) GCD = gcd(GCD, abs(a[u] - a[fa]));
    if(g[u].empty() && (GCD & (GCD - 1)) == 0) cnt++;
    for(auto v : g[u]) dfs(v, u, GCD, cnt, g, a);
}

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> g(n + 1);
    for(int i = 2; i <= n; i++)
    {
        int fa; cin >> fa;
        g[fa].push_back(i);
    }
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    int ans = 0;
    dfs(1, 0, 0, ans, g, a);
    cout << ans << "\n";
}
// 0000100000 ----> 0000011111 判断一个数是否是 2 的次幂 (x & (x - 1) == 0)

// 分析操作的本质: 当从集合中任选 2 个奇偶性相同的数 x 和 y, 操作后产生的数正好是两者的 "中点"
// 记 d = y - x 为这两者的差, 取中点后, 这个差就被 "二分" 为 d / 2 了, 如果后来再对新生成的数和原数继续操作, 效果就是不断将原本的间隔 / 2
// 要使得集合变为 "充实的", 则要让每对相邻元素的差都是 1
// 由于每次选的 x, y 奇偶性相同, 则 d 一定是偶数, 因此如果一个间隔 d 能经过若干次 / 2 变成 1, 那么 d 必须是 1 乘上一些 2 的幂次, 也就是说 d 必须是 2^k 形式

// 因此, 如果任意两个奇偶性相同的数的差 d 都是 2 的次幂, 则可以构成 "充实的" 集合
// 假设现在有三个相邻的数 a[i], a[i + 1], a[i + 2] 且 a[i] < a[i + 1] < a[i + 2]
// 如果 a[i] 和 a[i + 1] 奇偶性相同, 则有 d[i] = a[i + 1] - a[i] = 2 的次幂
// 如果 a[i] 和 a[i + 1] 奇偶性不同且 a[i + 1] 和 a[i + 2] 奇偶性不同, 则必有 a[i] 和 a[i + 2] 奇偶性相同, 则有 a[i + 2] - a[i] = 2 的次幂
// 又因为 a[i + 2] - a[i] = (a[i + 2] - a[i + 1]) + (a[i + 1] - a[i]) = d[i + 1] + d[i] = 2 的次幂
// 因此, 两种情况分别是 d[i] = 2^k 或者 d[i] + d[i + 1] = 2^k

// 现在分析局部 gcd, 设 g = gcd(d[i], d[i + 1])
// 由于整除理论, g | d[i] 且 g | d[i + 1], 那么必然有 g | (d[i] + d[i + 1]), 又因为上述证明了 d[i] + d[i + 1] 也是 2 的次幂形式
// 因此, g 必然是一个 2 的次幂形式
// 推广到整个集合, 有 g = gcd(d[1], d[2], ..., d[n - 1]) = 2 的次幂
// 综上, 我们证明了 "任意两个奇偶性相同的数的差 d 都是 2 的次幂" 等价于 gcd(d[1], d[2], ..., d[n - 1]) = 2 的次幂

// 因此, 对于从根到叶子的一条路径上, 我们只需要在 dfs 时记录它从根到叶子的点权差分 gcd, 到达叶子的时候判断一下 gcd 是否是 2 的幂次即可
 
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--)
    {
        solve();
    }
    return 0;
}
