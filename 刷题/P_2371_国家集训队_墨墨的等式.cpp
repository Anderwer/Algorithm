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

    u64 csp(u64 h)
    {
        u64 ans = 0;
        for(int i = 0; i < n; i++)
            if(h >= dis[i]) ans += (h - dis[i]) / n + 1;
        return ans;
    }
};

void solve()
{
    i64 n, l, r;
    cin >> n >> l >> r;
    vector<int> a;
    int mn = 1e9;
    for(int i = 1; i <= n; i++)
    {
        int x; cin >> x;
        if(x != 0)
        {
            a.push_back(x);
            mn = min(mn, x);
        }
    }

    CSP C(mn);
    for(int i = 0; i < mn; i++)
        for(auto x : a)
            if(x != mn) C.add(i, (i + x) % mn, x);

    C.dijkstra(0);
    i64 ans = C.csp(r) - C.csp(l - 1);
    cout << ans << '\n';
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
