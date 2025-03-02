#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
#define int long long

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1), b(m + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= m; i++) cin >> b[i];

    sort(b.begin() + 1, b.end());
    int cur = upper_bound(b.begin() + 1, b.end(), a[1]) - b.begin(); //b[1 ~ cur - 1] 是Keven 会做的题目
    sort(b.begin() + cur, b.end(), greater<int>()); //b[cur ~ m] 是Keven 不会做的题目且按降序排序 
    sort(a.begin() + 2, a.end()); // 给除了 Keven 以外的人的能力值排序

    for(int k = 1; k <= m; k++) //枚举k
    {
        int ans = 0;
        for(int i = 1; i <= m / k; i++) //枚举比赛场次
        {
            if(a[1] >= b[i * k])
            {
                ans++;
                continue;
            }
            int pos = lower_bound(a.begin() + 2, a.end(), b[i * k]) - a.begin();
            ans += (n - pos + 2);
        }
        cout << ans << " ";
    }
    cout << "\n";
}

signed main()
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
分析题意, 对于一个难度为 b[i] 的题目, 如果 b[i] > Keven 且有 x 个人的能力比 b[i] 大, 那么这一次比赛 Keven 的排名就为 1 + x
因此注意到, 小于等于 Keven 能力的人对答案没有任何影响, 可以去掉
现在考虑如何分组, 考虑贪心:
对于 Keven 会做的题目, 优先从小到大填充
对于 Keven 不会做的题目, 优先从大到小填充

接着处理查询不同 k 的答案
对于一个k , 可以分成 m / k 场比赛, 我们遍历每一场比赛, 第 i 场比赛的最难题是 b[i * k], 我们只需要判断 b[i * k] 和 Keven 的大小
如果Keven >= b[i * k], 那么这场比赛Keven 都会做, ans += 1
如果Keven < b[i * k], 那么二分找 a[] 中比 b[i * k] 大的人的下标pos, ans += (n - pos + 2)
*/