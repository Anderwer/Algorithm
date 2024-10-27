#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 4e5 + 10;

int a[N], b[N];
i64 f[N];
i64 pre[N];
multiset<i64> del[N];

void solve()
{
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) f[i] = 1e18, del[i].clear();
    for(int i = 1; i <= n; i++) cin >> a[i], pre[i] = pre[i - 1] + a[i];
    for(int i = 1; i <= n; i++) cin >> b[i];

    multiset<i64> st;
    st.insert(0);
    del[1].insert(0);

    for(int i = 1; i <= n; i++)
    {
        if(!st.empty()) f[i] = min(f[i], *st.begin()); //取可用点的最小值
        if(b[i] > i)
        {
            st.insert(f[i] + a[i]);
            del[b[i]].insert(f[i] + a[i]);
        }
        for(auto& x : del[i]) st.erase(st.find(x)); //删掉不在范围内的点
    }
    i64 ans = 0;
    for(int i = 1; i <= n; i++) ans = max(ans, pre[i] - f[i]);
    cout << ans << "\n";
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
问题概述 :
从 i = 1起, 一个人可以有两种决策
1. 选择第 i 个问题, 得分为a[i], 之后可以跳转到第 j 个问题, 其中 j ∈ [1, i - 1] 且第 j 个问题从未被选过

2. 不选择第 i 个问题, 不得分, 之后可以跳转到第 j 个问题, 其中 j ∈ [1, b[i]] 且第 j 个问题从未被选过

对于一个点 i , 如果选择不提交, 那么就相当于花费了a[i]的代价跳到 b[i]的位置
我们可以用 DP 获得跳到某一点的最小代价
注意 : 如果一个点 b[i] <= i, 那么跳它是没有意义的, 单纯的浪费分数

设 f[i] : 跳到点 i 的最小代价, 初始化为 1e18, f[1] = 0, f[b[1]] = a[1]
状态转移 : 当 i > 1 且 b[i] > i 时, f[i] = min(f[i], 区间[i + 1, b[i]]上一点 min(f[j]) + a[i])

对于快速获得区间 [i + 1, b[i]] 里的最小值 f[j], 且能够单点修改, 可以选择用线段树
由于遍历单调递增, 也可以用mutiset把有用的点塞进去,st.insert(f[i] + a[i])
然后再对 终点维护一个mutiset用于记录哪些点出了范围应该删除, del[b[i]].insert(f[i] + a[i])

最后答案 ans = max(pre[i] - f[i]);
*/