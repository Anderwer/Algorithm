一. 背包DP

1. 0-1背包 : f[i] = max(f[i], f[i - w[i]] + v[i]); 反向枚举容量

2. 完全背包 : f[i] = max(f[i], f[i - w[i]] + v[i]); 正向枚举容量

3. 多重背包(nmlog∑l[i]) : n种物品, 容量为m, 每种物品的重量为w[i], 每种物品的价值为v[i], 每种物品可以选l[i]次, 求最大价值
   思路 : 枚举每种物品, 对于每种物品, 把l[i]进行二进制分组, 得到x[], x[i]表示2^i个当前物品打包成的一个大物品, 然后对x[i]跑0-1背包, 其中x[]数组可以用码力优化
   代码实现 :   
            for(int i = 1; i <= n; i++)
            {
                int res = l[i];
                for(int k = 1; k <= res; res -= k, k *= 2;)
                    for(int j = m; j >= w[i] * k; j--) f[j] = max(f[j], f[j - w[i] * k] + v[i] * k);
                for(int j = m; j >= w[i] * res; j--) f[j] = max(f[j], f[j - w[i] * res] + v[i] * res);
            }

4. 分组背包 : n个物品, 容量为m, 每种物品的重量为w[i], 每种物品的价值为v[i], 每个物品属于一个组, 同组内最多只能选一个物品, 求最大价值
   思路 : 枚举每一组 , 对每一组跑0-1背包
   代码实现 :
            for(int i = 1; i <= N /*总组数*/; i++)
            {
                for(int j = m; j; j--)
                {
                    for(auto k : c[i])
                    {
                        if(v[k] <= j) f[j] = max(f[j], f[j - w[k]] + v[k]);
                    }
                }
            }

5. 多重背包(mn) : n种物品, 容量为m, 每种物品的重量为w[i], 每种物品的价值为v[i], 每种物品可以选k[i]次, 求最大价值
   思路 : 使用单调队列优化
   代码实现 :
            const int N = 1e2 + 10;
            const int M = 1e5 + 10;
            int n, m, last = 0, now = 1;
            int v[N], w[N], k[N], f[2][M];
            deque<int> q;

            cin >> n >> m;
            for(int i = 1; i <= n; i++) cin >> v[i] >> w[i] >> k[i];
            for(int i = 1; i <= n; i++)
            {
                for(int y = 0; y < w[i]; y++)
                {
                    deque<int>().swap(q); //清空队列
                    for(int x = 0; x * w[i] + y <= m; x++)
                    {
                        while(!q.empty() && q.front() < x - k[i]) q.pop_front();
                        while(!q.empty() && f[last][q.back() * w[i] + y] - q.back() * v[i] < f[last][x * w[i] + y] - x * v[i]) q.pop_back();
                        q.push_back(x);
                        f[now][x * w[i] + y] = f[last][q.front() * w[i] + y] - q.front() * v[i] + x * v[i];
                    }
                }
                swap(last, now);
            }
            cout << f[last][m];

 
二. 区间DP

一般步骤 :
    1. 枚举区间长度 L ∈ [1, n - 1]
    2. 枚举区间起点 i ∈ [1, n - L] , 确定区间终点 j = i + L;
    3. 枚举区间分界线 k ∈ [i, j) ; 
    4. 在分界线内写转移

例题 : 石子合并

    for(int l = 1; l <= n - 1; l++) //枚举区间长度
    {
        for(int i = 1; i <= n - l; i++) //枚举起点
        {
            int j = i + l;//终点
            for(int k = i; k < j; k++) //枚举分界线
            {
                f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j] + pre[j] - pre[i - 1]);
                dp[i][j] = max(dp[i][j], dp[i][k] + dp[k + 1][j] + pre[j] - pre[i - 1]);
            }
        }
    }

