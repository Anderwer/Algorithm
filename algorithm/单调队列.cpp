#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

// 单调队列模板
// 适用范围:
// 1. 滑动窗口最小值 / 最大值
// 2. 维护区间最值转移的 DP
//
// 约定:
// 1. 下面模板默认数组 a 使用 1 下标
// 2. 若传入 vector, 默认 a[1..n] 有效, a[0] 位置留空
// 3. 队列中存的是下标, 不是值

struct MonotonicQueue
{
    deque<int> q;
    vector<i64>* a;

    MonotonicQueue() : a(nullptr) {}

    void bind(vector<i64>& arr)
    {
        a = &arr;
        q.clear();
    }

    void clear()
    {
        q.clear();
    }

    bool empty() const
    {
        return q.empty();
    }

    int front() const
    {
        return q.front();
    }

    int back() const
    {
        return q.back();
    }

    i64 frontValue() const
    {
        return (*a)[q.front()];
    }

    i64 backValue() const
    {
        return (*a)[q.back()];
    }

    // 维护单调递增队列, 队首为最小值
    void pushMin(int pos)
    {
        while(!q.empty() && (*a)[q.back()] >= (*a)[pos]) q.pop_back();
        q.push_back(pos);
    }

    // 维护单调递减队列, 队首为最大值
    void pushMax(int pos)
    {
        while(!q.empty() && (*a)[q.back()] <= (*a)[pos]) q.pop_back();
        q.push_back(pos);
    }

    // 删除已经离开窗口的下标
    void popOutdated(int left)
    {
        while(!q.empty() && q.front() < left) q.pop_front();
    }
};


// 滑动窗口最小值
// 返回每个长度为 k 的窗口的最小值
vector<i64> getWindowMin(vector<i64>& a, int k)
{
    int n = (int)a.size() - 1;
    vector<i64> ans;
    if(n <= 0 || k <= 0 || k > n) return ans;

    MonotonicQueue q;
    q.bind(a);

    for(int i = 1; i <= n; i++)
    {
        q.pushMin(i);
        q.popOutdated(i - k + 1);
        if(i >= k) ans.push_back(q.frontValue());
    }
    return ans;
}

// 滑动窗口最大值
// 返回每个长度为 k 的窗口的最大值
vector<i64> getWindowMax(vector<i64>& a, int k)
{
    int n = (int)a.size() - 1;
    vector<i64> ans;
    if(n <= 0 || k <= 0 || k > n) return ans;

    MonotonicQueue q;
    q.bind(a);

    for(int i = 1; i <= n; i++)
    {
        q.pushMax(i);
        q.popOutdated(i - k + 1);
        if(i >= k) ans.push_back(q.frontValue());
    }
    return ans;
}


/*
DP 中常见用法:

1. 维护区间最小值
设状态转移需要用到区间 [i - m, i - 1] 中某个值的最小位置

int l = 1, r = 0;
vector<int> q(n + 1);
for(int i = 1; i <= n; i++)
{
    while(l <= r && q[l] < i - m) l++;
    while(l <= r && a[q[r]] >= a[i]) r--;
    q[++r] = i;

    // 当前区间最小值位置为 q[l]
    // 最小值为 a[q[l]]
}

2. 维护区间最大值
int l = 1, r = 0;
vector<int> q(n + 1);
for(int i = 1; i <= n; i++)
{
    while(l <= r && q[l] < i - m) l++;
    while(l <= r && a[q[r]] <= a[i]) r--;
    q[++r] = i;

    // 当前区间最大值位置为 q[l]
    // 最大值为 a[q[l]]
}

说明:
1. 单调递增队列维护最小值
2. 单调递减队列维护最大值
3. 队首永远是当前窗口最优下标
4. 时间复杂度 O(n)
*/