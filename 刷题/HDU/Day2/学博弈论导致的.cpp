#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    i64 r, b, m;
    cin >> r >> b >> m;
    if((r + 2 * b) % 4 == 0) cout << "Bob\n";
    else cout << "Alice\n";
}

// 首先, 拿宝盒是没有具体影响的, 因为:
// 如果拿一个宝盒并放一个蓝宝石, 第二个人可以选择操作 3, 这样既不会改变宝石的数量也不会改变先后手顺序
// 如果拿一个宝盒并放一个红宝石, 第二个人可以选择操作 1, 这样既不会改变宝石的数量也不会改变先后手顺序
// 如果拿一个宝盒并放一个红宝石和一个蓝宝石, 第二个人可以选择操作 3, 这样既不会改变宝石的数量也不会改变先后手顺序

// 因此, 这场游戏只和 r, b 有关
// 有用的操作只有前 4 个, 对前 4 个操作进行转换: 设 每个红宝石价值 1 块钱, 每个蓝宝石价值 2 块钱
// 1. 拿走 1 ~ 3 块钱
// 2. 拿走 1 块钱
// 3. 拿走 2 ~ 3 块钱
// 4. 拿走 3 块钱
// 所有操作取并集, 可变成一个操作 : 拿走 1 ~ 3 块钱
// 因此问题转化成: 现在有 r + 2 * b 块钱, 每次拿走 1 ~ 3 块钱, 问轮到谁刚好能拿完
// 这是经典的 Bash Game, 如果初始的钱 mod 4 == 0, 则先手必败, 否则先手必胜 

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
