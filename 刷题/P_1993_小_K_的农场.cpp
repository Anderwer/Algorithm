#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

struct SPFA
{
    vector<i64> dis;
    vector<int> cnt;
    vector<int> vis;
    vector<vector<array<i64, 2>>> G;

    int n;
    SPFA() {};
    SPFA(int n_)
    {
        n = n_;
        G = vector<vector<array<i64, 2>>>(n + 1);
        dis = vector<i64>(n + 1, 2e18);
        cnt = vector<int>(n + 1, 0);
        vis = vector<int>(n + 1, 0);
    }

    void add(int u, int v, int w)
    {
        G[u].push_back({v, w});
    }

    bool spfa()
    {
        queue<int> q;
        dis[0] = 0;
        vis[0] = 1;
        q.push(0);
        for(int i = 1; i <= n; i++) add(0, i, 0);
        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            vis[u] = 0;
            for(auto [v, w] : G[u])
            {
                if(dis[v] > dis[u] + w)
                {
                    dis[v] = dis[u] + w;
                    cnt[v] = cnt[u] + 1;
                    if(cnt[v] > n)
                        return true;
                    if(vis[v] == false)
                        q.push(v), vis[v] = 1;
                }
            }
        }
        return false;
    }
};

void solve() // x_j <= x_i + c      add(i, j, c)
{
    int n, m;
    cin >> n >> m;

    SPFA S(n);
    for(int i = 1; i <= m; i++)
    {
        int op;
        cin >> op;
        if(op == 1) // a - b >= c ----> b <= a - c
        {
            int a, b, c;
            cin >> a >> b >> c;
            S.add(a, b, -c);
        }
        else if(op == 2) // a - b <= c ----> a <= b + c
        {
            int a, b, c;
            cin >> a >> b >> c;
            S.add(b, a, c);
        }
        else if(op == 3) // a - b <= 0 && a - b >= 0
        {
            int a, b;
            cin >> a >> b;
            S.add(a, b, 0);
            S.add(b, a, 0);
        }
    }
    if(S.spfa() == false) cout << "Yes\n";
    else cout << "No\n";
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    //cin >> t;
    while(t--)
    {
        solve();
    }
    return 0;
}
