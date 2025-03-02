#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n, m;
    cin >> n >> m;
    if(m > 2 * n - 1)
    {
        cout << "NO\n";
        return;
    }

    vector<vector<int>> ans(2 * n + 1, vector<int>(2 * n));
    for(int i = 1; i <= n; i++) //枚举颜色
    {
        int p1 = 2 * i - 1;
        int p2 = 2 * i;
        for(int right = 1; right <= 2 * n - 1; right++) //枚举右边的点
        {
            ans[p1][right] = i;
            ans[p2][right] = i;
            p1 = (p1 + 1) % (2 * n);
            p2 = (p2 + 1) % (2 * n);
            if(p1 == 0) p1 = 2 * n;
            if(p2 == 0) p2 = 2 * n;
        }
    }

    cout << "YES\n";
    for(int i = 1; i <= 2 * n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            cout << ans[i][j] << ' ';
        }
        cout << "\n";
    }
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
输出的是邻接矩阵, g[i][j] 表示 <i, j> 之间的颜色
现在需要构造边的颜色使得对于每一个环不存在所有边颜色相同
现在考虑在左右用单独一种颜色连边, 为了不成环, 我们在连接时要构成像树一样的结构(因为树中无环)
因为左边有 2n 个点, 右边有 m 个点, 因此最多可以连 (2n + m - 1) 条边
因为我们可以染 n 种颜色, 因此整个图没有环的情况是最多有 n * (2n + m - 1) 条边
让 n * (2n + m - 1) >= 2 * n * m
化简得 : m <= 2n - 1, 如果 m > 2n - 1 则不可能构造

现在考虑 m = 2n - 1 的情况, 观察到对于每一种颜色的边, 右边每个点的度都为 2
对于第 1 种颜色, 我们可以先选取左边 1, 2两个点和右边的点 1 相连, 然后往下走 'z'字形
对于第 2 种颜色, 我们可以先选取左边 3, 4两个点和右边的点 1 相连, 然后往下走 'z'字形, 然后发现左边的 1, 2两个点还没连, 这时候把这两个点搬下来再连'z'
...

因此, 总结规律:
对于第 i 种颜色, 先选择 2i - 1, 2i 两个点与右边的 1 相连
再选择 2i, 2i + 1 两个点与右边的 2 相连
如果点超过了 2n, 应该模上 2n
*/