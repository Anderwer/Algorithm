#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 1e5 + 10;

char s[2][N];
int f[N][3];
int n;

int check(int i, int flag1, int flag2)
{
    int res = 0;
    int A1 = 0, A2 = 0, A = 0;
    if(flag1 == 1 && flag2 == 1)
    {
        if(i + 3 > n) return -1;
        for(int x = i + 1; x <= i + 3; x++) if(s[0][x] == 'A') A1++;
        for(int x = i + 1; x <= i + 3; x++) if(s[1][x] == 'A') A2++;
        if(A1 >= 2) res++;
        if(A2 >= 2) res++;
    }
    if(flag1 == 1 && flag2 == 2)
    {
        if(i + 2 > n) return -1;
        if(s[0][i + 1] == 'A') A++;
        if(s[1][i + 1] == 'A') A++;
        if(s[0][i + 2] == 'A') A++;
        if(A >= 2) res++;
    }
    if(flag1 == 1 && flag2 == 3)
    {
        if(i + 2 > n) return -1;
        if(s[0][i + 1] == 'A') A++;
        if(s[1][i + 1] == 'A') A++;
        if(s[1][i + 2] == 'A') A++;
        if(A >= 2) res++;
    }
    if(flag1 == 2 && flag2 == 1)
    {
        if(i + 2 > n) return -1;
        if(s[0][i + 2] == 'A') A++;
        if(s[1][i + 2] == 'A') A++;
        if(s[1][i + 1] == 'A') A++;
        if(A >= 2) res++;
    }
    if(flag1 == 2 && flag2 == 2)
    {
        if(i + 4 > n) return -1;
        for(int x = i + 2; x <= i + 4; x++) if(s[0][x] == 'A') A1++;
        for(int x = i + 1; x <= i + 3; x++) if(s[1][x] == 'A') A2++;
        if(A1 >= 2) res++;
        if(A2 >= 2) res++;
    }
    if(flag1 == 3 && flag2 == 1)
    {
        if(i + 2 > n) return -1;
        if(s[0][i + 2] == 'A') A++;
        if(s[1][i + 2] == 'A') A++;
        if(s[0][i + 1] == 'A') A++;
        if(A >= 2) res++;
    }
    if(flag1 == 3 && flag2 == 2)
    {
        if(i + 4 > n) return -1;
        for(int x = i + 2; x <= i + 4; x++) if(s[1][x] == 'A') A1++;
        for(int x = i + 1; x <= i + 3; x++) if(s[0][x] == 'A') A2++;
        if(A1 >= 2) res++;
        if(A2 >= 2) res++;
    }
    return res;
}
void solve()
{
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> s[0][i];
    for(int i = 1; i <= n; i++) cin >> s[1][i];
    for(int i = 1; i <= n; i++) f[i][0] = f[i][1] = f[i][2] = -1;
    f[0][0] = 0;
    for(int i = 0; i <= n; i++)
    {
        for(int j = 0; j <= 2; j++)
        {
            if(f[i][j] == -1) continue;
            if(j == 0)
            {
                f[i + 3][0] = max(f[i + 3][0], f[i][0] + check(i, 1, 1));
                f[i + 1][1] = max(f[i + 1][1], f[i][0] + check(i, 1, 2));
                f[i + 1][2] = max(f[i + 1][2], f[i][0] + check(i, 1, 3));
            }
            if(j == 1)
            {
                f[i + 2][0] = max(f[i + 2][0], f[i][1] + check(i, 2, 1));
                f[i + 3][1] = max(f[i + 3][1], f[i][1] + check(i, 2, 2));
            }
            if(j == 2)
            {
                f[i + 2][0] = max(f[i + 2][0], f[i][2] + check(i, 3, 1));
                f[i + 3][2] = max(f[i + 3][2], f[i][2] + check(i, 3, 2));
            }
        }
    }
    cout << f[n][0] << "\n";
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
一眼dp
由于圈地只有 四种 "L" 型和在一排的形状
注意 : 如果你在一行选择了水平形状, 那么在另一行中也要使用它
设 f[i][0] : 到第 i 列为止, 前 i 列全部被填满, 且i + 1 列没有选
设 f[i][1] : 到第 i 列为止, 前 i 列全部被填满, 且i + 1 列选了上面的格子
设 f[i][2] : 到第 i 列为止, 前 i 列全部被填满, 且i + 1 列选了下面的格子

状态转移:
假如当前已得到了 f[i][0], 则有以下转移:
    f[i + 3][0] = max(f[i + 3][0], f[i][0] + check) (1, 1)
    f[i + 1][1] = max(f[i + 1][1], f[i][0] + check) (1, 2)
    f[i + 1][2] = max(f[i + 1][2], f[i][0] + check) (1, 3)

假如当前已得到了 f[i][1], 则有以下转移:
    f[i + 2][0] = max(f[i + 2][0], f[i][1] + check) (2, 1)
    f[i + 3][1] = max(f[i + 3][1], f[i][1] + check) (2, 2)

假如当前已得到了 f[i][2], 则有以下转移:
    f[i + 2][0] = max(f[i + 2][0], f[i][2] + check) (3, 1)
    f[i + 3][2] = max(f[i + 3][2], f[i][2] + check) (3, 2)
*/