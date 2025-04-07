#include <bits/stdc++.h>
#define int long long
using i64 = long long;
using namespace std;
const int p = 998244353;

int qpow(int a, int b)
{
    int res = 1;
    while(b)
    {
        if(b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1), L(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) cin >> L[i];

    int ans = 1;
    for(int i = 0; i <= n; i++)
    {
        int sum = 0;
        for(int j = 0; j <= 31; j++)
            if(a[i] & (1 << j)) sum++;

        int cur = qpow(2, sum);
        if(L[i] < a[i])
        {
            for(int j = 31; j >= 0; j--)
            {
                if(a[i] & (1 << j)) sum--;
                if(((a[i] >> j) & 1) && !((L[i] >> j) & 1)) cur = (cur - qpow(2, sum) + p) % p;
                if(!((a[i] >> j) & 1) && ((L[i] >> j) & 1)) break;
            }
        }
        ans = (ans * cur % p) % p;
    }
    cout << ans << "\n";
}

// 结论题, 对于组合数 C(a, b) 当 a & b == b 时为奇数, 否则为偶数
// 但是现在 b 的取值多了一个 L 的限制
// 如果 L >= a, 由于要满足 a & b == b, 则一共有 2 ^ sum 种 b 的取值, 其中 sum 是 a 中二进制为 1 的数量
// 如果 L < a, 则要讨论:
// 我们从高位到低位考虑, 如果 a 中第 i 位二进制位为 1 但 L 中为 0, 说明这一位不可取, 我们减去第 i 位后面的所有情况
// 直到 a 中第 i 位二进制位为 0 且 L 中为 1, 即为答案


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
