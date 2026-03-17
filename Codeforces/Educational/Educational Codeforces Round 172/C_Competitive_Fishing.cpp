#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
#define int long long

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<char> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    
    vector<int> suf_0(n + 2, 0);
    vector<int> suf_1(n + 2, 0);
    for(int i = n; i >= 1; i--)
    {
        if(a[i] == '0')
        {
            suf_0[i] = suf_0[i + 1] + 1;
            suf_1[i] = suf_1[i + 1];
        }
        else
        {
            suf_1[i] = suf_1[i + 1] + 1;
            suf_0[i] = suf_0[i + 1];
        }
    }
    vector<int> effect;
    for(int i = 2; i <= n; i++) //区间[i, n]
    {
        effect.push_back(suf_1[i] - suf_0[i]);
    }
    sort(effect.begin(), effect.end(), greater<int>());
    int ans = 1, sum = 0;
    for(auto v : effect)
    {
        sum += v;
        ans++;
        if(sum >= k) break;
    }
    if(sum < k) cout << -1 << "\n";
    else cout << ans << "\n";
}

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

/*
                
0 0 0 1 1 1 0 | 1 0 1 0 1 1 0 1 1
                i
我们假设当前在位置 i 前面切一刀, 区间 [i, n] 每条鱼的分数都 + 1, 区间[1, i - 1] 的分数都不变
因此, 区间[1, i - 1]并不会影响我们的答案 Bob - Alice
假设在没切这一刀时,区间[i, n]是第 x 个区间, 区间[i, n]中 Alice 钓了 a 条鱼, Bob 钓了 b 条鱼, 那么它们的分数差就为 cost1 = (b - a) * (x - 1)
现在切了一刀, 区间[i, n] 变为了第 x + 1 个区间, 此时[i, n] 产生的分数差就为 cost2 = (b - a) * x
因此, 切完一刀给答案的影响就是 cost2 - cost1 = (b - a)

所以, 我们可以枚举每一个可以切的位置, 计算它给答案带来的影响
然后从大到小挑选切的位置直到 >= k
*/