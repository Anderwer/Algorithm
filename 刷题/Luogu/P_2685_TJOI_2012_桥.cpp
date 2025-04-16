#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

struct DSPP // Delete Shortest Path Problem
{
    #define lc u << 1
    #define rc u << 1 | 1
    using PII = pair<i64, i64>;
    const i64 INF = 1e18;
    int n, m, cnt;
    vector<vector<array<i64, 3>>> g;
    vector<array<i64, 3>> e;
    vector<i64> dist1, distn;
    vector<int> nxt, L, R, ID, nxtid, ispath;
    vector<i64> Min;

    DSPP() {};
    DSPP(int n_, int m_)
    {
        n = n_, m = m_;
        g = vector<vector<array<i64, 3>>>(n + 10);
        e = vector<array<i64, 3>>(m + 10);
        dist1 = distn = vector<i64>(n + 10, INF);
        nxt = nxtid = L = R = ispath = vector<int>(n + 10, 0);
        ID = vector<int>(m + 10, 0);
        Min = vector<i64>(n * 4 + 10);
    }

    void add(i64 u, i64 v, i64 w, i64 id)
    {
        e[id] = {u, v, w};
        g[u].push_back({v, w, id});
        g[v].push_back({u, w, id});
    }

    void dijkstra(int s, vector<i64>& dis, int op)
    {
        for(int i = 1; i <= n; i++) dis[i] = INF;
        dis[s] = 0;
        priority_queue<PII, vector<PII>, greater<PII>> q;
        q.push({0, s});

        while(!q.empty())
        {
            auto [dis_u, u] = q.top();
            q.pop();
            for(auto [v, w, id] : g[u])
            {
                if(dis[v] > dis_u + w)
                {
                    dis[v] = dis_u + w;
                    q.push({dis[v], v});

                    nxt[v] = u;
                    nxtid[v] = id;

                    if(ispath[v] == false)
                    {
                        if(op == 1) R[v] = R[u];
                        if(op == 2) L[v] = L[u];
                    }
                }
            }
        }
    }

    void build(int u, int l, int r)
    {
        if(l > r) return;
        Min[u] = INF;
        if(l == r) return;
        int mid = (l + r) / 2;
        build(lc, l, mid);
        build(rc, mid + 1, r); 
    }

    void update(int u, int l, int r, int x, int y, i64 val)
    {
        if(x <= l && y >= r)
        {
            Min[u] = min(Min[u], val);
            return;
        }
        int mid = (l + r) / 2;
        if(x <= mid) update(lc, l, mid, x, y, val);
        if(y > mid) update(rc, mid + 1, r, x, y, val);
    }

    i64 query(int u, int l, int r, int pos)
    {
        if(l == r) return Min[u];
        i64 res = Min[u];
        int mid = (l + r) / 2;
        if(pos <= mid) res = min(res, query(lc, l, mid, pos));
        else res = min(res, query(rc, mid + 1, r, pos));
        return res;
    }

    void init()
    {
        for(int i = 0; i <= m; i++) ID[i] = -1;
        L[1] = R[1] = cnt = 0;
        ispath[1] = true;
        int cur = 1;
        while(cur != n)
        {
            int id = nxtid[cur];
            ID[id] = ++cnt;

            cur = nxt[cur];
            ispath[cur] = true;
            L[cur] = R[cur] = cnt;
        }
    }

    void dspp()
    {
        dijkstra(n, distn, 0);

        init();
        build(1, 1, cnt);
        dijkstra(n, distn, 1);
        dijkstra(1, dist1, 2);

        for(int i = 1; i <= m; i++)
        {
            auto [u, v, w] = e[i];
            if(ID[i] == -1)
            {
                if(L[u] + 1 <= R[v])
                    update(1, 1, cnt, L[u] + 1, R[v], dist1[u] + w + distn[v]);
                if(L[v] + 1 <= R[u])
                    update(1, 1, cnt, L[v] + 1, R[u], dist1[v] + w + distn[u]);
            }
        }
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;

    DSPP D(n, m);
    for(int i = 1; i <= m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        D.add(u, v, w, i);
    }
    D.dspp();

    i64 ans = D.dist1[n], cnt = 0;
    for(int i = 1; i <= D.cnt; i++) 
    {
        i64 Min = D.query(1, 1, D.cnt, i);
        if(Min < 1e18) ans = max(ans, Min);
    }
    for(int i = 1; i <= D.cnt; i++)
    {
        if(D.query(1, 1, D.cnt, i) == ans) cnt++;
    }
    if(ans == D.dist1[n]) cnt = m;
    cout << ans << " " << cnt << "\n";
}

signed main()
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
