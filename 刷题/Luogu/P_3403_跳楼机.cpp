#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
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
    u64 h, x, y, z;
    cin >> h >> x >> y >> z;

    CSP C(x);
    u64 ans = 0;
    for(int i = 0; i < x; i++)
    {
        C.add(i, (i + y) % x, y);
        C.add(i, (i + z) % x, z);
    }
    C.dijkstra(0);
    ans = C.csp(h - 1);
    cout << ans << "\n";
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
