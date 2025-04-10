#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n, u, k, hq;
    cin >> n >> u >> k >> hq;
    priority_queue<array<int, 3>> pq;
    priority_queue<array<int, 2>> pq2;
    for(int i = 1; i <= n; i++)
    {
        int a, h; cin >> a >> h;
        pq.push({-h, -a, -i});
        pq2.push({a, i});
    }

    int ans = 0;
    vector<int> cnt(n + 1, 0);
    vector<int> died(n + 1, 0);
    while(hq > 0)
    {
        if(pq.empty()) break;
        auto cur = pq.top();
        pq.pop();
        int blood = -cur[0];
        if(cnt[-cur[2]] == 0) blood -= u;
        else blood -= (u / 2);
        cnt[-cur[2]]++;
        if(blood <= 0)
        {
            ans++;
            died[-cur[2]] = 1;
            while(!pq2.empty() && died[pq2.top()[1]]) pq2.pop();
        }
        if(!pq2.empty()) hq -= pq2.top()[0];
        
        if(blood > 0 && cnt[-cur[2]] < k) pq.push({-blood, cur[1], cur[2]}); 
    }
    cout << ans << '\n';
}

// 按照题意排序优先级: 血量 > 攻击力 > 编号
// 注意到, 每个怪物最多被攻击 k 次, 而 k <= 1000
// 因此, 可以用 O(n * k) 或者 O(n * k * logn) 进行模拟
// 根据题意, 在优先队列中维护 {血量, 攻击力, 编号} 小顶堆
// 再开一个数组记录每个编号的敌人被攻击的次数, 如果攻击次数 < k 则更新数据后再放入优先队列中
// 此外, 每次被攻击时都取当前怪物中所有攻击力最高的数值, 因此还需要用 大顶堆 维护攻击力

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
