#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 2e5 + 10;
int a[N];

void solve()
{
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];

    
    int L = 1, R = n;
    int L_ans = 1, R_ans = n;
    while(L <= R)
    {
        int len = R - L + 1; //区间长度
        int L_left = L - a[L] + 1, L_right = L + a[L] - 1;
        int R_left = R - a[R] + 1, R_right = R + a[R] - 1;
        L_ans = max({L_ans, L_left, R_left});
        R_ans = min({R_ans, L_right, R_right}); //区间取交集

        if(a[L] >= len && a[R] >= len) L++, R--; // 左右都满足
        else if(a[L] >= len) L++; //以右端点为起点, 判断是否能到左端点
        else if(a[R] >= len) R--; //以左端点为起点, 判断是否能到右端点
        else 
        {
            cout << 0 << "\n";
            return;
        }
    }
    cout << R_ans - L_ans + 1 << '\n';
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
注意到 , 对于一个点 i 
区间[i - a[i] + 1, i + a[i] - 1]的任何一个点作为起点都能到达 i 点

一开始是一个大区间, 左端为1, 右端为n

对左端点检测是否能到右端, 对右端点检测是否能到左端

如果能到达, 则缩小区间

否则, 则总是存在不能到达的点, 答案总交集为 0

每个点都存在一个这样的区间, 给所有的区间取交集, 最后的交集区间里面的数量为答案
*/