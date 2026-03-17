#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

const int N = 2e5 + 10;
int cnt[30][2]; //cnt[i][0] : 统计偶数位置, cnt[i][1]: 统计奇数位置
int num0[N][30], num1[N][30]; //num0[i][j] : 在偶数位上, 到位置i为止 字符为j 的数量

void solve()
{
    int n;
    string s;
    cin >> n >> s;
    s = " " + s;
    
    if(n % 2 == 0)
    {
        for(int i = 0; i < 30; i++) cnt[i][0] = cnt[i][1] = 0;
        for(int i = 1; i <= n; i++) cnt[s[i] - 'a'][i & 1]++;
        int max_0 = 0, max_1 = 0;
        for(int i = 0; i < 26; i++) max_0 = max(max_0, cnt[i][0]), max_1 = max(max_1, cnt[i][1]);
        int ans = n - (max_0 + max_1);
        cout << ans << "\n";
        return;
    }

    for(int i = 1; i <= n; i++)
        for(int j = 0; j < 30; j++) num0[i][j] = num1[i][j] = 0;
    
    for(int i = 1; i <= n; i++)
    {
        if(i & 1) num1[i][s[i] - 'a'] = 1;
        else num0[i][s[i] - 'a'] = 1;
        for(int j = 0; j < 26; j++) num0[i][j] += num0[i - 1][j], num1[i][j] += num1[i - 1][j];
    }

    int ans = 1e9;
    for(int i = 1; i <= n; i++) //枚举被删的是哪个字符
    {
        int len = n - 1;
        //因为最终字符串只有两种字符, 可以枚举一下分别是哪两种 O(26^2)
        //设a字符为奇数位,b字符为偶数为
        //统计答案时: a字符有 num1[i - 1][a] + num0[n][a] - num0[i][a]
        //           b字符有 num0[i - 1][b] + num1[n][b] - num1[i][b]
        
        for(int a = 0; a < 26; a++)
        {
            for(int b = 0; b < 26; b++)
            {
                int a_num = num1[i - 1][a] + num0[n][a] - num0[i][a];
                int b_num = num0[i - 1][b] + num1[n][b] - num1[i][b];
                ans = min(ans, len - (a_num + b_num));
            }
        }
    }
    cout << ans + 1 << "\n"; //删去操作, +1次

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
先统计一下字符串中 奇数位和偶数位的字符数量

如果删除一个字符, 则奇数位变偶数位

如果n是奇数, 则必须删除一个字符, ans++
如果n是偶数, 则不能删除

当n 是偶数时, ans += (n - (max_1 + max_0))

当n 是奇数时, 需要删除, 尝试删除每一位
当删除第 i 位时, 前面 i - 1 位的奇偶性不变, 从i + 1 到 n 的奇偶性互换

*/