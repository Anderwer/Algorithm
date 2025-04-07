#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<i64> a(m + 1);
    vector c(n + 1, vector<i64>(m + 1)), w(n + 1, vector<i64>(m + 1));
    for(int i = 1; i <= m; i++) cin >> a[i];
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++) cin >> c[i][j];
        for(int j = 1; j <= m; j++) cin >> w[i][j];
    }

    vector<priority_queue<array<i64, 2>>> pq(m + 1); //pq[i] : {val, idx} 小根堆, val 取负
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            pq[j].push({-c[i][j], i});

    vector<int> cnt(n + 1, 0); //统计 n 个公司的能力通过数
    int cur = 0; //到目前为止通过了多少个公司
    while(true)
    {
        vector<int> ok; //统计哪些公司合法
        for(int i = 1; i <= m; i++)
        {
            while(!pq[i].empty() && a[i] >= -pq[i].top()[0])
            {
                cnt[pq[i].top()[1]]++;
                if(cnt[pq[i].top()[1]] == m) ok.push_back(pq[i].top()[1]);
                pq[i].pop();
            }
        }

        cur += ok.size();
        for(auto id : ok)
            for(int j = 1; j <= m; j++)
                a[j] += w[id][j];

        if(cur == n) break;
        if(ok.empty())
        {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}

// 由于 n x m <= 3e6, 因此考虑 O(n x m) 或者 O(nmlog(nm))的做法
// 首先考虑贪心, 我们为了不断提升自己的能力, 会将能通过面试的公司优先进行面试
// 因此我们可以用优先队列维护 m 种能力, 先记录每一种能力当前可以通过哪些公司的面试
// 统计出来以后看是否有公司的能力通过数量 == m, 如果有则代表这个公司可以通过
// 如果当前不存在一个这样的公司, 则不存在合法情况

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
