#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n, m;
    cin >> n >> m;
    
    vector<array<i64, 2>> a(n + 1), b(m + 1);
    for(int i = 1; i <= n; i++) cin >> a[i][0] >> a[i][1];
    for(int i = 1; i <= m; i++) cin >> b[i][0] >> b[i][1];

    i64 inf = 1e18;
    i64 f1max = -inf, f1min = inf, f2max = -inf, f2min = inf;
    for(int i = 1; i <= n; i++)
    {
        f1max = max(f1max, a[i][0] + a[i][1]);
        f1min = min(f1min, a[i][0] + a[i][1]);
        f2max = max(f2max, a[i][0] - a[i][1]);
        f2min = min(f2min, a[i][0] - a[i][1]);
    }

    i64 ans = 1e18;
    for(int i = 1; i <= m; i++)
    {
        i64 cur = -1e18;
        cur = max(cur, f1max - (b[i][0] + b[i][1]));
        cur = max(cur, (b[i][0] - b[i][1]) - f2min);
        cur = max(cur, f2max - (b[i][0] - b[i][1]));
        cur = max(cur, (b[i][0] + b[i][1]) - f1min);
        ans = min(ans, cur);
    }
    cout << ans << "\n";
}

// n 个客户, m 个配送站, 都有一个坐标<x, y>, 求最小的最大曼哈顿距离
// 对于 |x1 - x2| + |y1 - y2| 可以选择拆绝对值
//   |x1 - x2| + |y1 - y2|
// = (x1 - x2) + (y1 - y2) = (x1 + y1) - (x2 + y2)
// = (x2 - x1) + (y1 - y2) = (x2 - y2) - (x1 - y1)
// = (x1 - x2) + (y2 - y1) = (x1 - y1) - (x2 - y2)
// = (x2 - x1) + (y2 - y1) = (x2 + y2) - (x1 + y1)

// 显然, 式子中一共有四种情况, 且只有 x + y 和 x - y 两种情形
// 因此, 对于 n 个客户, 维护它们的 x + y 的最大值和最小值以及 x - y 的最大值和最小值
// 然后对于每个选点, 都可以进行 O(1) 求出最大曼哈顿距离
// 我们让式子中的 x2 和 y2 作为配送站坐标, 

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
