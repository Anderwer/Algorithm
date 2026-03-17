#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

// 二维前缀和 + 二维差分模板
// 约定:
// 1. 下标默认从 1 开始
// 2. 传入的矩阵 a 应满足 a[1..n][1..m] 有效, 第 0 行和第 0 列留空
// 3. 若需要多次使用, 重新 init 即可
//
// 常见用途:
// 1. 二维前缀和: 快速求子矩阵和
// 2. 二维差分: 快速做矩形区域加减
//
// 核心公式:
//
// 前缀和:
// pre[i][j] = pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1] + a[i][j]
//
// 子矩阵和 [x1..x2][y1..y2]:
// sum = pre[x2][y2] - pre[x1 - 1][y2] - pre[x2][y1 - 1] + pre[x1 - 1][y1 - 1]
//
// 差分标记矩形 [x1..x2][y1..y2] 加 val:
// diff[x1][y1] += val
// diff[x2 + 1][y1] -= val
// diff[x1][y2 + 1] -= val
// diff[x2 + 1][y2 + 1] += val

template<typename T>
struct PrefixSum2D
{
    int n, m;
    vector<vector<T>> pre;

    PrefixSum2D() {}
    PrefixSum2D(int n_, int m_)
    {
        init(n_, m_);
    }

    PrefixSum2D(const vector<vector<T>>& a)
    {
        init(a);
    }

    void init(int n_, int m_)
    {
        n = n_;
        m = m_;
        pre.assign(n + 1, vector<T>(m + 1, T{}));
    }

    void init(const vector<vector<T>>& a)
    {
        n = (int)a.size() - 1;
        m = (int)a[1].size() - 1;
        pre.assign(n + 1, vector<T>(m + 1, T{}));

        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= m; j++)
            {
                pre[i][j] = pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1] + a[i][j];
            }
        }
    }

    T query(int x1, int y1, int x2, int y2) const
    {
        if(x1 > x2 || y1 > y2) return T{};
        return pre[x2][y2] - pre[x1 - 1][y2] - pre[x2][y1 - 1] + pre[x1 - 1][y1 - 1];
    }
};

template<typename T>
struct Difference2D
{
    int n, m;
    vector<vector<T>> diff;

    Difference2D() {}
    Difference2D(int n_, int m_)
    {
        init(n_, m_);
    }

    void init(int n_, int m_)
    {
        n = n_;
        m = m_;
        diff.assign(n + 2, vector<T>(m + 2, T{}));
    }

    // 基于原矩阵 a 构造二维差分
    void build(const vector<vector<T>>& a)
    {
        n = (int)a.size() - 1;
        m = (int)a[1].size() - 1;
        diff.assign(n + 2, vector<T>(m + 2, T{}));

        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= m; j++)
            {
                add(i, j, i, j, a[i][j]);
            }
        }
    }

    // 给矩形 [x1..x2][y1..y2] 加 val
    void add(int x1, int y1, int x2, int y2, const T& val)
    {
        if(x1 > x2 || y1 > y2) return;
        diff[x1][y1] = diff[x1][y1] + val;
        diff[x2 + 1][y1] = diff[x2 + 1][y1] - val;
        diff[x1][y2 + 1] = diff[x1][y2 + 1] - val;
        diff[x2 + 1][y2 + 1] = diff[x2 + 1][y2 + 1] + val;
    }

    // 还原最终矩阵
    vector<vector<T>> get() const
    {
        vector<vector<T>> a(n + 1, vector<T>(m + 1, T{}));
        auto cur = diff;
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= m; j++)
            {
                cur[i][j] = cur[i][j] + cur[i - 1][j] + cur[i][j - 1] - cur[i - 1][j - 1];
                a[i][j] = cur[i][j];
            }
        }
        return a;
    }
};

/*
使用示例:

1. 二维前缀和
vector<vector<i64>> a(n + 1, vector<i64>(m + 1));
for(int i = 1; i <= n; i++)
    for(int j = 1; j <= m; j++)
        cin >> a[i][j];

PrefixSum2D<i64> pre(a);
cout << pre.query(x1, y1, x2, y2) << "\n";

2. 二维差分
Difference2D<i64> diff(n, m);
diff.add(x1, y1, x2, y2, val);
diff.add(x3, y3, x4, y4, val2);
auto b = diff.get();

3. 由原矩阵构造差分, 再继续修改
Difference2D<i64> diff;
diff.build(a);
diff.add(x1, y1, x2, y2, val);
auto b = diff.get();
*/