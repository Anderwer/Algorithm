#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 1e6 + 10;
vector<int> g[N];
vector<int> din(N, 0);
vector<int> tp;

bool topsort(int n)
{
    queue<int> q;
    for(int i = 1; i <= n; i++)
        if(din[i] == 0) q.push(i);
    
    while(!q.empty())
    {
        auto x = q.front();
        q.pop();
        tp.push_back(x);
        for(auto& y : g[x])
            if(--din[y] == 0) q.push(y);
    }
    return tp.size() == n;
}

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<array<int, 3>> a(m + 1);
    for(int i = 1; i <= m; i++) cin >> a[i][0] >> a[i][1] >> a[i][2];

    for(int i = 1; i <= m; i++)
    {
        int x = a[i][0], y = a[i][1], col = a[i][2];
        if(col != ((y + 1) / 2) && col != (2 * n - x + 1) && col != (2 * n + x - y / 2))
        {
            cout << "No\n";
            for(int j = 1; j <= m; j++)
            {
                int x = a[j][0], y = a[j][1], col = a[j][2];
                g[(y + 1) / 2].clear();
                g[(2 * n - x + 1)].clear();
                g[(2 * n + x - y / 2)].clear();
                din[col] = 0;
            }
            return;
        }
        
        if(col != (y + 1) / 2) g[(y + 1) / 2].push_back(col), din[col]++;
        if(col != (2 * n - x + 1)) g[(2 * n - x + 1)].push_back(col), din[col]++;
        if(col != (2 * n + x - y / 2)) g[(2 * n + x - y / 2)].push_back(col), din[col]++;
    }

    if(topsort(n * 3)) cout << "Yes\n";
    else cout << "No\n";

    for(int i = 1; i <= m; i++)
    {
        int x = a[i][0], y = a[i][1], col = a[i][2];
        g[(y + 1) / 2].clear();
        g[(2 * n - x + 1)].clear();
        g[(2 * n + x - y / 2)].clear();
        din[col] = 0;
    }
    tp.clear();
}

// 一个刷子可以影响的格子数大约有 n 个, 因此反向考虑
// 考虑一个格子(i, j)可以被 3 个刷子影响, 分别是来自下方的第 [j / 2](上取整) 个, 左边的第 (2n + i - j / 2) 个, 右边的第 (2n - i + 1) 个刷子
// 因为一个格子的最终颜色是由最后一个刷它的刷子决定的, 我们也知道第 i 个格子的最终颜色, 因此如果影响这个格子的 3 个刷子都不是最终颜色, 则不可能实现构造

// 如果符合上述条件, 我们设这个格子的最终颜色为 col, 则第 col 个刷子一定是最后刷的, 其他两个刷子要先刷
// 因此我们把另外两个刷子指向第 col 个刷子, 代表在刷 col 之前要刷完前两个刷子
// 于是对于 m 个已经确定的 col, 我们都可以对每个 col 进行建边, 最终成一个图
// 对于这个图, 如果图中存在环, 那么说明存在冲突(比如说在刷颜色 1 之前要刷颜色 2, 但是刷颜色 2 之前要刷颜色 1), 此时无法实现构造

// 综上, 对 m 个 col 进行连边, 将颜色不是 col 的刷子连向 col
// 对于有向图, 使用拓扑排序判断是否为 DAG
// 如果是 DAG 则可以构造

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
