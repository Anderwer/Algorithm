#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    vector<array<int, 3>> f(n + 1, {-1, -1, -1});
    f[1][0] = 1;
    f[1][1] = 0;
    for(int i = 1; i < n; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(f[i][j] == -1) continue; //无状态
            if(j == 0) //转移 f[i][0] ----> f[i + 1][0] & f[i + 1][1]
            {
                if(f[i][0] < a[i + 1]) f[i + 1][0] = max(f[i + 1][0], f[i][0] + 1);
                else if(f[i][0] == a[i + 1]) f[i + 1][0] = max(f[i + 1][0], f[i][0]);
                else f[i + 1][0] = max(f[i + 1][0], f[i][0] - 1);
                f[i + 1][1] = max(f[i][0], f[i + 1][1]);
            }
            if(j == 1) //转移 f[i][1] ----> f[i + 1][1] & f[i + 1][2]
            {
                if(f[i][1] < a[i + 1]) f[i + 1][2] = max(f[i + 1][2], f[i][1] + 1);
                else if(f[i][1] == a[i + 1]) f[i + 1][2] = max(f[i + 1][2], f[i][1]);
                else f[i + 1][2] = max(f[i + 1][2], f[i][1] - 1);
                f[i + 1][1] = max(f[i + 1][1], f[i][1]);
            }
            if(j == 2) //转移 f[i][2] ----> f[i + 1][2]
            {
                if(f[i][2] < a[i + 1]) f[i + 1][2] = max(f[i + 1][2], f[i][2] + 1);
                else if(f[i][2] == a[i + 1]) f[i + 1][2] = max(f[i + 1][2], f[i][2]);
                else f[i + 1][2] = max(f[i + 1][2], f[i][2] - 1);
            }
        }
    }
    cout << max(f[n][1], f[n][2]) << "\n";
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
题意: 选取一个区间 [L, R], 在区间之外的如果 a[i] > x, 则 x++, 如果 a[i] < x, 则 x--, 如果 a[i] == x, 则 x 不变, x 初始为 0

考虑划分型DP
设状态:
f[i][0] : 到位置 i 时且未进入区间 [L, R] 得到的最大值
f[i][1] : 到位置 i 时且进入了区间 [L, R] 得到的最大值
f[i][2] : 到位置 i 时且已经出了区间 [L, R] 得到的最大值

显然有 f[i][0] ----> f[i + 1][0] & f[i + 1][1]
也有 f[i][1] ----> f[i + 1][1] & f[i + 1][2]
也有 f[i][2] ----> f[i + 1][2]
*/ 