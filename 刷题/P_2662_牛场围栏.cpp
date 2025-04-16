#include <bits/stdc++.h>
using u64 = unsigned long long;
using i64 = long long;
using namespace std;

struct CSP // Congruence Shortest Path
{
    using u64 = unsigned long long;
    using PII = pair<u64, u64>;
    const u64 INF = -1ull;
    int n;
    vector<vector<array<u64, 2>>> g;
    vector<u64> dis;

    CSP() {};
    CSP(int n_)
    {
        n = n_;
        g = vector<vector<array<u64, 2>>>(n + 10);
        dis = vector<u64>(n + 10);
    }

    void add(u64 u, u64 v, u64 w)
    {
        g[u].push_back({v, w});
    }

    void dijkstra(u64 s)
    {
        for(int i = 0; i <= n; i++) dis[i] = INF;
        dis[s] = 0;
        priority_queue<PII, vector<PII>, greater<PII>> q;
        q.push({0, s});

        while(!q.empty())
        {
            auto [dis_u, u] = q.top();
            q.pop();
            for(auto [v, w] : g[u])
            {
                if(dis[v] > dis_u + w)
                {
                    dis[v] = dis_u + w;
                    q.push({dis[v], v});
                }
            }
        }
    }

    u64 csp(u64 h) // 返回区间 [0, h] 的统计数
    {
        u64 ans = 0;
        for(int i = 0; i < n; i++)
            if(h >= dis[i]) ans += (h - dis[i]) / n + 1;
        return ans;
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> v(n + 1);
    for(int i = 1; i <= n; i++) cin >> v[i];

    set<int> a;
    for(int i = 1; i <= n; i++)
        for(int j = 0; j <= min(v[i], m); j++) a.insert(v[i] - j);

    a.erase(0);
    if(!a.empty() && (*a.begin()) == 1) cout << -1 << "\n";
    else
    {
        int mn = (*a.begin());
        a.erase(mn);
        CSP C(mn);
        for(int i = 0; i < mn; i++)
            for(auto x : a) C.add(i, (i + x) % mn, x);
        C.dijkstra(0);

        for(int i = 0; i < mn; i++)
        {
            if(C.dis[i] == C.INF)
            {
                cout << -1 << "\n";
                return;
            }
        }
        u64 ans = 0;
        for(int i = 1; i < mn; i++) ans = max(ans, C.dis[i] - mn);
        cout << ans << "\n";
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    while(t--)
    {
        solve();
    }
    return 0;
}
