#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    i64 d, r, x, y;
    cin >> d >> r >> x >> y;
    
    double ans = 0;
    if(y >= d) ans = abs(hypot(x, y - d) - r);
    else if(y <= -d) ans = abs(hypot(x, y + d) - r);
    else ans = min(abs(x - r), abs(x + r));
    cout << round(ans) << "\n";
}

// 分类讨论, 如果点在 (-d, d) 范围内, 则答案就是点到直线的距离
// 否则, 如果点在上半部分的圆那边, 点到圆弧的最短距离就是点到圆心的距离 - 半径
// 在下半部分的圆那边也同理

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
