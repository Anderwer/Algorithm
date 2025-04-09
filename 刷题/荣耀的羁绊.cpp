#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void dfs()
{
    
}

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> heroes(5, 0);
    for(int i = 0; i < 5; i++)
    {
        int cnt; cin >> cnt;
        while(cnt--)
        {
            int x; cin >> x;
            heroes[i] |= (1 << (x - 1));
        }
    }

    vector<vector<int>> to(n, vector<int>(5, 0));
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            cin >> to[i][j];
        }
    }

    vector<int> f(1 << n, 0);
    vector<int> p(5, 0);
    for(int i = 0; i < 5; i++) p[i] = i;

    do
    {
        vector<int> v(5, 0);
        for(int i = 0; i < 5; i++) v[i] = heroes[p[i]];
        dfs();
    }
    while(next_permutation(p.begin(), p.end()))
}

// 由于 n <= 15, 考虑对所有情况进行状态压缩 
// 设 f[i]: 状态为 i 的所有合法情况
// 考虑如何转移, 假设 n = 4, 在二进制下当前状态为 1101, 对于第 3 个英雄的转移, 有 f[1101] += f[(1101) ^ (1 << (3 - 1))]
// 因此, 对于每一个英雄, 枚举所有状态, 作为当前英雄对阵容的贡献

// 在动态转移之前, 需要 DP 初始化, 需要搭配 dfs 搜索
// 具体的, 先枚举五个人不同分路的每一种情况, 对于每一种情况, 先获取每个人会玩的英雄(状态压缩存储)
// 传统 dfs 对每种情况进行剪枝并统计合法方案数
// 至此, 预处理完成

// 
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
