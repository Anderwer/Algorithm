#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using namespace std;
const u64 M = 10000000000001029;

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<u64> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    vector<u64> f(64, -1ull);
    for(int i = 1; i <= n; i++)
        for(int j = 0; j < 64; j++)
            if(a[i] & (1ull << j)) 
                f[j] = f[j] & a[i];
            
    u64 ans = 0;
    while(q--)
    {
        u64 x; cin >> x;
        u64 cur = 0, res = -1ull;
        for(int j = 63; j >= 0; j--)
        {
            if(x & (1ull << j)) cur = cur | f[j];
            else res = min(res, cur | f[j]);
        }
        res = min(res, cur);
        ans = ans ^ (res % M) % M;
    }
    cout << ans << "\n";
}

// 已知自然数集 S 中的 n 个数, 要求新的数 y 使得 y ∈ S 且 y 尽可能小
// 首先为了满足一个尽可能小的数在自然数集 S 中, 我们要知道每一个二进制位上对应的已知数是谁
// 设 f[i]: n 个数中第 i 位二进制位为 1 的最小数
// 显然, 取任意个 f[i] 按位或 得到的数就属于自然数集 S

// 至此, 为了求新的数 y 使得 y ∈ S 且 y >= x
// 由于要满足 y >= x, 我们先分析 x 的每一个二进制位, 从高位开始考虑(贪心)
// 如果当前 x 的第 i 位二进制为 1, 那么让 cur | f[i]
// 然后统计 x 的哪些二进制位是 0, 并从中选择一位变为 1, 并让这一位 按位或 上该位对应的最小数, 因为 y >= x


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
