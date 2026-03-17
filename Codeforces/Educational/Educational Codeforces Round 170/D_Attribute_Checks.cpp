#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 5050;

int f[N][N];
int cnt1[N][N], cnt2[N][N];

void solve()
{
    int n, m, cnt = 0;
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
    {
        int x; cin >> x;
        if(x == 0)
        {
            cnt++;
            continue;
        }
        if(x > 0 && cnt >= x) cnt1[cnt][x]++; //对智力有贡献的检测点
        if(x < 0 && cnt >= abs(x)) cnt2[cnt][abs(x)]++; //对力量有贡献的检测点
    }

    for(int i = 1; i <= cnt; i++) 
    {
        for(int j = 1; j <= i; j++)
        {
            cnt1[i][j] += cnt1[i][j - 1];
            cnt2[i][j] += cnt2[i][j - 1]; //处理贡献前缀和
        }
    }

    int ans = 0;
    for(int i = 1; i <= cnt; i++) //枚举一共多少加点
    {
        for(int j = 0; j <= i; j++) //枚举点了多少点智力
        {
            f[i][j] = max(f[i][j], f[i - 1][j] + cnt1[i][j] + cnt2[i][i - j]); //第 i 点选了力量
            if(j > 0) f[i][j] = max(f[i][j], f[i - 1][j - 1] + cnt1[i][j] + cnt2[i][i - j]); //第 i 点选了智力
            ans = max(ans, f[i][j]);
        }
    }
    cout << ans << "\n";
}
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
    return 0;
}

/*
一眼dp
设 f[i][j] : 获得了 i 次加点, 点了 j 点"智力" 所能通过的测试最多数量

状态转移:
f[i][j] = max(f[i][j], f[i - 1][j] + 前 i 次加点选了 j 次智力的贡献和 + 前 i 次加点选了 i - j 次力量的贡献和)
f[i][j] = max(f[i][j], f[i - 1][j - 1] + 前 i 次加点选了 j 次智力的贡献和 + 前 i 次加点选了 i - j 次力量的贡献和)

对于贡献和, 我们可以开两个前缀和数组分别计算 智力的贡献和 还有 力量的贡献和
设 cnt1[i][j] 为 前 i 次加点过程中, 满足当前点数 i >= r 的智力检测点前缀和
设 cnt2[i][j] 为 前 i 次加点过程中, 满足当前点数 i >= r 的力量检测点前缀和

*/