#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
i64 n, m, k;

bool check(i64 mid, vector<int>& h, vector<int>& x) //mid 是攻击次数
{
    vector<array<i64, 2>> seg;
    for(int i = 1; i <= n; i++)
    {
        i64 damage = (h[i] + mid - 1) / mid; //向上取整
        if(m < damage) continue;
        i64 L = x[i] - m + damage;
        i64 R = x[i] + m - damage;
        seg.push_back({L, 1});
        seg.push_back({R + 1, -1});
    }
    if(seg.empty()) return false;
    sort(seg.begin(), seg.end());
    i64 cnt = 0;
    for(auto [x, y] : seg)
    {
        cnt += y;
        if(cnt >= k) return true;
    }
    return false;
}

void solve()
{
    cin >> n >> m >> k;
    vector<int> h(n + 1), x(n + 1);
    for(int i = 1; i <= n; i++) cin >> h[i];
    for(int i = 1; i <= n; i++) cin >> x[i];

    i64 l = 1, r = 1E9 + 10;
    i64 ans = -1;
    while(l <= r)
    {
        i64 mid = (l + r) / 2;
        if(check(mid, h, x) == true)
        {
            r = mid - 1;
            ans = mid;
        }
        else l = mid + 1;
    }
    cout << ans << "\n";
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
题目要求最小攻击次数, 具有二段性, 考虑二分答案
我们可以二分攻击次数 cnt, 使得存在一个位置 p 使得至少 k 个敌人在 cnt 次攻击后被击败
设当前某个敌人的为位置在 x[i], 要使敌人被打死, 我们每次攻击的伤害为 m - distance(p, x[i])
而这名敌人要保证每次工具的伤害 >= (h[i] / cnt)上取整, 这样才能在 cnt 次打死
因此, 转化为 m - distance(p, x[i]) >= [h[i] / cnt]
即 |p - x[i]| <= m - [h[i] / cnt], 我们要保证 m - [h[i] / cnt] >= 0, 否则无意义
因此, x[i] - m + [h[i] / cnt] <= p <= x[i] + m - [h[i] / cnt]

我们在二分攻击次数时, 每次对每个敌人的合法的 p 的区间进行标记
然后跑扫描线(差分)是否存在至少 k 区间覆盖
如果存在, 则极值点左移, 否则右移
*/