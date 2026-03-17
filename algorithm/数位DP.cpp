#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

// 数位 DP 模板
// 适用范围:
// 1. 统计区间 [L, R] 内满足某种数位性质的数的个数
// 2. 数位性质只和“已经填了哪些位”有关
// 3. 常见限制:
//    - 某些数字不能出现
//    - 数位和满足条件
//    - 相邻数字关系满足条件
//    - 某种状态自动机约束
//
// 核心思想:
// 1. 先写一个函数 calc(x), 统计 [0, x] 内的合法数个数
// 2. 区间答案通常为 calc(R) - calc(L - 1)
// 3. DFS 按从高位到低位枚举当前位
// 4. 常见状态:
//    - pos   : 当前处理到第几位
//    - state : 题目自定义状态
//    - lead  : 前导零是否还没结束
//    - lim   : 当前位是否受到上界限制
//
// 使用方式:
// 1. 先根据题意修改 dfs 的状态定义
// 2. 再修改转移中的合法性判断
// 3. 若状态较少, 可以直接记忆化
// 4. 若状态较复杂, 可自行扩展维度或改成 map 记忆化

struct DigitDP
{
    // dig[1..n], dig[1] 是最低位, dig[n] 是最高位
    vector<int> dig;

    // 下面这组记忆化数组只是一个“骨架示例”
    // 当前示例状态含义:
    // f[pos][sum][last + 1]
    // - pos: 还剩多少位没填
    // - sum: 当前数位和
    // - last: 上一位填了什么, -1 表示前面还没有出现非前导零数字
    //
    // 你做题时可以按题意改成:
    // - f[pos][state]
    // - f[pos][sum][mod]
    // - f[pos][state1][state2]
    // 等等
    static const int MAX_POS = 20;
    static const int MAX_SUM = 200;

    i64 f[MAX_POS][MAX_SUM][11];
    bool vis[MAX_POS][MAX_SUM][11];

    DigitDP()
    {
        memset(vis, 0, sizeof(vis));
    }

    void init()
    {
        memset(vis, 0, sizeof(vis));
    }

    // 这个 dfs 是“示例版骨架”
    // 当前示例统计的是:
    // [0, x] 内满足“相邻位不相等”的数字个数
    //
    // 你做题时通常只需要改三处:
    // 1. 状态定义
    // 2. 合法性判断
    // 3. 终止条件
    i64 dfs(int pos, int sum, int last, bool lead, bool lim)
    {
        if(pos == 0)
        {
            // 到达结尾时返回是否算作一个合法数
            // 当前模板默认把 0 也算进去
            return 1;
        }

        if(!lim && !lead && vis[pos][sum][last + 1])
        {
            return f[pos][sum][last + 1];
        }

        int up = lim ? dig[pos] : 9;
        i64 res = 0;

        for(int d = 0; d <= up; d++)
        {
            bool nlead = lead && (d == 0);
            bool nlim = lim && (d == up);

            // ---------- 合法性判断示例 ----------
            // 当前示例: 相邻非前导零数字不能相等
            if(!nlead && last != -1 && d == last) continue;
            // -----------------------------------

            int nsum = sum + d;
            int nlast = nlead ? -1 : d;

            res += dfs(pos - 1, nsum, nlast, nlead, nlim);
        }

        if(!lim && !lead)
        {
            vis[pos][sum][last + 1] = true;
            f[pos][sum][last + 1] = res;
        }
        return res;
    }

    // 统计 [0, x] 的答案
    i64 calc(i64 x)
    {
        if(x < 0) return 0;
        if(x == 0) return 1;

        dig.clear();
        dig.push_back(0);
        while(x)
        {
            dig.push_back(x % 10);
            x /= 10;
        }

        return dfs((int)dig.size() - 1, 0, -1, true, true);
    }

    // 统计 [l, r] 的答案
    i64 rangeQuery(i64 l, i64 r)
    {
        if(l > r) return 0;
        init();
        i64 ansR = calc(r);
        init();
        i64 ansL = calc(l - 1);
        return ansR - ansL;
    }
};

/*
==========================
最常见的改法
==========================

1. 统计数位和等于 k
- 状态里保留 sum
- 终止条件改成: return sum == k;

2. 统计数位和模 m 等于 0
- 把 sum 改成 mod
- 转移时 nmod = (mod * 10 + d) % m
- 终止条件: return mod == 0;

3. 统计不包含某些数字
- 在枚举 d 时 if(d == forbidden) continue;

4. 统计相邻位满足大小关系
- 保留 last
- 按题意判断 if(...) continue;

5. 统计某个字符串模式不出现
- 用 KMP / AC 自动机状态做 state
- 转移时更新到 nextState
- 若到达非法状态则 continue

==========================
典型写法
==========================

DigitDP solver;
cout << solver.rangeQuery(L, R) << "\n";

==========================
注意事项
==========================

1. 数位 DP 通常写成 [0, R] - [0, L - 1]
2. lim 为 true 时一般不能记忆化
3. lead 为 true 时, 状态含义要特别小心
4. 0 是否算合法数, 要看题意修改终止条件
5. 若返回值可能很大, 用 i64
*/