#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void dfs(int cur, int cnt, int n, vector<int>& f, vector<int>& curHero, vector<vector<int>>& A) // A[i][j] 第 i 个英雄可以走 j 分路
{
    if(cnt == 5) // 选完了 5 个英雄
    {
        f[cur]++;
        return;
    }
    for(int i = 0; i < n; i++) // 当前在选分路为 cnt 的英雄, 枚举 n 个英雄
    {
        if(cur & (1 << i)) continue; // 第 i 个英雄之前选过了
        if((curHero[cnt] & (1 << i)) && A[i][cnt]) // 选择当前分路的玩家会用第 i 个英雄
            dfs(cur | (1 << i), cnt + 1, n, f, curHero, A);
    }
}

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> heroSet(5, 0);
    for(int i = 0; i < 5; i++)
    {
        int cnt; cin >> cnt;
        while(cnt--)
        {
            int x; cin >> x;
            heroSet[i] |= (1 << (x - 1));
        }
    }

    vector<vector<int>> A(n, vector<int>(5, 0));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < 5; j++) cin >> A[i][j];

    vector<int> f(1 << (n + 1), 0);
    vector<int> p(5, 0); // p[i] 表示玩家 p[i] 选择分路 i
    for(int i = 0; i < 5; i++) p[i] = i;

    do
    {
        vector<int> curHero(5); // curHero[j] 表示选择分路 i 的玩家会用的英雄集合
        for(int i = 0; i < 5; i++) curHero[i] = heroSet[p[i]];
        dfs(0, 0, n, f, curHero, A);
    }
    while(next_permutation(p.begin(), p.end()));

    /*
    for(int i = 1; i <= ((1 << n) - 1); i++) //对所有状态进行转移, 例如 n = 4 时一共有状态从 0001 到 1111, 即 从 1 到 2^n - 1
    {
        for(int j = 0; j < n; j++) // 枚举当前状态的每一位
        {
            if(i & (1 << j)) f[i] += f[i ^ (1 << j)];
        }
    }
    */
    
    // 上面的dp更新方法不对, 因为要确保上一个状态被更新过, 类似于背包DP 中的先枚举物品, 再枚举背包容量
    for(int j = 0; j < n; j++) 
    {
        for(int i = 1; i <= (1 << n) - 1; i++) //对所有状态进行转移, 例如 n = 4 时一共有状态从 0001 到 1111, 即 从 1 到 2^n - 1
        {
            if(i & (1 << j)) f[i] += f[i ^ (1 << j)];
        }
    }
    
    while(q--)
    {
        int ban; cin >> ban;
        int banSet = 0;
        while(ban--)
        {
            int x; cin >> x;
            banSet |= (1 << (x - 1));
        }
        cout << f[((1 << n) - 1) ^ banSet] << "\n";
    }
}

// 为了快速得到某些英雄被禁用后的总方案数, 由于 n <= 15, 考虑预处理所有情况
// 这里用 (1 << n) 种情况表示某些英雄是可选的状态(状态压缩)
// 设 f[i]: 二进制下可选英雄集合为状态 i 时的方案数
// 状态转移: 对于当前状态 i, 寻找它的每一位二进制位, 当找到第 x 位为 1 时,  状态 i 可由上一个状态 i ^ (1 << x) 转移而来
// 因此对于每一位 x , 枚举所有状态, 如果当前状态选择过 x, 则有 f[i] += f[i ^ (1 << x)], 其中 i & (1 << x) == 1
// 初始化: 状态转移之前, 首先要将所有合法阵容(记为状态 v)的方案数置为 1, 即对于任意合法阵容 v, 有 f[v] = 1

// 至此, 问题转化为如何统计所有合法阵容, 考虑暴力搜索:
// 1. 枚举五个人走不同分路的情况, 即为 [0, 1, 2, 3, 4] 进行全排列
// 2. 对于每一种分路分配的情况, 我们得到了每个人会用的英雄, 考虑 dfs 枚举所有合法阵容

// tips: 每个人会用的英雄集合同样可以用状态压缩存储, 由于英雄编号 x 是从 1 开始的, 我们将二进制第 0 位作为编号 1 的英雄, 因此每次将 heroSet[i] |= (1 << (x - 1)) 意为第 i 个人会用英雄 x


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
