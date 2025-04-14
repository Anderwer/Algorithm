#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

struct Floyd
{
    const int INF = (1 << 31) - 1;
    int n;
    vector<vector<i64>> f;
    vector<vector<i64>> G;
    vector<vector<int>> mid;
    vector<int> path;

    Floyd() {};
    Floyd(int n_)
    {
        n = n_;
        f = vector<vector<i64>>(n + 1, vector<i64>(n + 1, INF));
        G = vector<vector<i64>>(n + 1, vector<i64>(n + 1, INF));
        mid = vector<vector<int>>(n + 1, vector<int>(n + 1, 0));
    }

    void add(i64 u, i64 v, i64 w)
    {
        G[u][v] = min(G[u][v], w); //处理重边
        f[u][v] = G[u][v];
    }

    void init(int m) // 读入 m 条边
    {
        for(int i = 1; i <= n; i++)
            f[i][i] = G[i][i] = 0;

        for(int i = 1; i <= m; i++)
        {
            i64 u, v, w;
            cin >> u >> v >> w;
            add(u, v, w);
            add(v, u, w); //无向图
        }
    }

    void dfs(int i, int j)
    {
        if(mid[i][j] == 0) return;
        dfs(i, mid[i][j]);
        path.push_back(mid[i][j]);
        dfs(mid[i][j], j);
    }

    int floyd()
    {
        i64 ans = INF;
        for(int k = 1; k <= n; k++)
        {
            for(int i = 1; i < k; i++)
                for(int j = i + 1; j < k; j++)
                {
                    if(ans > f[i][j] + G[i][k] + G[k][j])
                    {
                        ans = f[i][j] + G[i][k] + G[k][j];
                        path.clear();
                        path.push_back(i);
                        dfs(i, j);
                        path.push_back(j);
                        path.push_back(k);
                    }
                }

            for(int i = 1; i <= n; i++)
                for(int j = 1; j <= n; j++)
                {
                    if(f[i][j] > f[i][k] + f[k][j])
                    {
                        f[i][j] = f[i][k] + f[k][j];
                        mid[i][j] = k;
                    }
                }
        }
        return ans;
    }
};

void solve()
{
    const int INF = (1 << 31) - 1;
    int n, m;
    cin >> n >> m;

    Floyd F(n);
    F.init(m);
    int ans = F.floyd();
    if(ans == INF) cout << "No solution.";
    else
    {
        for(auto v : F.path) cout << v << " ";
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
