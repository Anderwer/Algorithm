#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

i64 get_x(i64 px, i64 b, i64 k)
{
    if(px < b) return 0ll;
    else if(px == b) return 1ll;
    return (px - b) / k + 1ll;
}

i64 cal(i64 L, i64 R, i64 b, i64 k)
{
    return get_x(R, b, k) - get_x(L - 1, b, k); 
}

void solve()
{
    i64 k, b, c, v;
    cin >> k >> b >> c >> v;
    
    i64 cur = 0, ans = 0;
    for(int i = 63; i >= 0; i--)
    {
        if((v >> i) & 1) // v 的第 i 位是 1
        {
            if((c >> i) & 1)
            {
                cur += (1ll << i); //尝试将 px 的第 i 位变为 1
                ans += cal(cur, cur + (1ll << i) - 1, b, k);
                cur -= (1ll << i); //复原
            }
            else
            {
                ans += cal(cur, cur + (1ll << i) - 1, b, k);
                cur += (1ll << i); //必须将 px 的第 i 位变为 1
            }
        }
        else if((c >> i) & 1) // v 的第 i 位是 0 且 c 的第 i 位是 1
        {
            cur += (1ll << i); //必须将 px 的第 i 位变为 1
        }
    }

    cur -= b;
    if(cur >= 0 && cur % k == 0) ans++; //检查是否存在恰好相等的情况
    cout << ans << "\n";
}

// (p ^ c) <= v
// v = 100011010
// c = 001001101
// c, v 已知, 则可推断出 p 的某一位的限制
// 从高位到低位考虑:
// 如果 v 的第 i 位是 1:
//      如果当前 c 的第 i 位是 1, 则让当前的 cur += (1 << i), 问题转变为如何快速求区间 px ∈ [cur, cur + (1 << i) - 1] 的合法 x 数量
//      对于 kx + b ∈ [L, R], x 可取的最大值为 (R - b) / k, 最小值为 (L - b) / k, 因此合法的 x 有 (R - b) / k - (L - 1 - b) / k 个
//      如果当前 c 的第 i 为是 0, 则直接统计, 并把 cur 的第 i 位设置成 1

// 如果 v 的第 i 位是 0:
//      c 的第 i 位是 0 的情况不需要考虑
//      当 c 的第 i 位是 1 时, 必须将 cur 的第 i 位设置成 1

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
