#include <bits/stdc++.h>
#define int long long
using i64 = long long;
using namespace std;
const int N = 2e5 + 10;
i64 a[N];

void solve()
{
    i64 n, k;
    cin >> n >> k;
    for(int i = 1; i <= n; i++) cin >> a[i];
    i64 sum = 0, mx = 0;
    for(int i = 1; i <= n; i++) sum += a[i], mx = max(mx, a[i]);

    int ans = 0;
    for(int i = n; i >= 1; i--)
    {
        i64 m = (sum + k) / i; //最多能分成 m 组 , 每组 i 大小
        if(m * i >= sum && m * i <= (sum + k) && mx <= m)
        {
            ans = i;
            break;
        }
    }
    cout << ans << "\n";
    
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
分牌策略

ans 最大为 n , 当且仅当这副牌中的所有种类的牌数都相同

假设最终的每组牌大小为 x, 一共分成了 m 组
那么要满足以下条件:
    总牌数 sum = m * x
    每种牌的数量小于等于 m


x 范围 : 1 <= x <= n 
枚举x, 并判断是否满足条件


*/

