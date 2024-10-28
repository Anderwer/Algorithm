#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    vector<int> b(m);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < m; i++) cin >> b[i];

    vector<vector<int>> nxt(n, vector<int>(m));
    for(int k = 0; k < m; k++) //处理好nxt 数组
    {
        int sum = 0, r = -1;
        for(int i = 0; i < n; i++)
        {
            while(r < n && sum <= b[k]) sum += a[++r];
            nxt[i][k] = r;
            sum -= a[i];
        }
    }

    vector<vector<int>> f(n + 10, vector<int> (m + 10, 1e9));
    f[0][0] = 0;
    for(int k = 0; k < m; k++)
    {
        for(int i = 0; i < n; i++)
        {
            f[nxt[i][k]][k] = min(f[nxt[i][k]][k], f[i][k] + m - k - 1);
            if(k + 1 <= m) f[i][k + 1] = min(f[i][k], f[i][k + 1]);
        }
    }

    int ans = 1e9;
    for(int k = 0; k < m; k++) ans = min(ans, f[n][k]);
    if(ans == 1e9) cout << -1 << "\n";
    else cout << ans << "\n";
    //for(int i = 1; i <= m; i++) cout << f[n][i] << " ";
    //for(int i = 1; i <= m; i++) cout << nxt[1][i] << " ";
    //cout << f[1][1] << "\n";
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
首先我们知道, 每一次消去的代价是 m - k, 这意味着 k 越大需要的代价越小
由于 n * m <= 3e5, 我们可以考虑复杂度O(nm)
考虑DP
设 f[i][j] : 删除长度为 i 的前缀时, 选择 k = j 时的最小代价
状态转移:
    对于操作一, 仅仅让 k + 1, 则 可以从 f[i][j] 免费过渡到 f[i][j + 1]
    对于操作二, 我们要选择一段连续子数组, a[i + 1], a[i + 2], ..., a[i + x], 并删除它们, 再转移到 f[i + x][j], 且 f[i + x][j] = f[i][j] + m - k
    为了快速找到操作二中的每一个 i 对应的 x, 我们可以预处理一个 nxt[i][k] = x 的数组
    类似于利用滑动窗口, 先枚举 k, 再枚举 i

*/