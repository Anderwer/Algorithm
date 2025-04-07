#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int P, n, k;
    cin >> P >> n >> k;
    vector<array<int, 2>> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i][0] >> a[i][1];
    
    vector<double> c1; // 打折
    vector<i64> c2; // 降价
    for(int i = 1; i <= n; i++)
    {
        if(a[i][0] == 0) c1.push_back(a[i][1] * 0.1);
        else c2.push_back(a[i][1]);
    }
    sort(c1.begin(), c1.end());
    sort(c2.begin(), c2.end(), greater<i64>());

    vector<double> pre1(n + 1, 1);
    vector<i64> pre2(n + 1, 0);
    for(int i = 1; i <= n; i++)
    {
        if(i <= c1.size()) pre1[i] = pre1[i - 1] * c1[i - 1];
        else pre1[i] = pre1[i - 1];
    }
    for(int i = 1; i <= n; i++)
    {
        if(i <= c2.size()) pre2[i] = pre2[i - 1] + c2[i - 1];
        else pre2[i] = pre2[i - 1];
    }

    double ans = P;
    for(int i = 0; i <= k; i++)
    {
        double res = P * pre1[i];
        res -= pre2[k - i];
        if(res < 0) res = 0;
        ans = min(ans, res);
    }
    printf("%.2f\n", ans);
}

// 考虑贪心, 先将打折券从小到大排, 将降价券从大到小排
// 维护价格, 比较两种券对答案的贡献
// 假设现有一张折扣为 a 的券, 还有一张降价 b 元的券, 当前价格为 P 元
// 如果先用打折券再用降价券, 对答案的贡献为 P(1 - a) + b = P - aP + b
// 如果先用降价券再用打折券, 对答案的贡献为 b + (P - b)(1 - a) = P - aP + b - (1 - a)b
// 显然, 上面的方法对答案贡献更大

// 因此有如下决策:
// 枚举 i 张券用于打折, k - i 张券用于降价
// 为了快速得到前 i 张打折券和 k - i 张降价券, 用前缀和预处理

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
