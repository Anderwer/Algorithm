#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

// 欧拉路 / 欧拉回路模板
// 包含:
// 1. 有向图欧拉路
// 2. 无向图欧拉路
//
// 说明:
// 1. 点编号默认 1..n
// 2. 路径中会存经过的点序列
// 3. 若返回 true, 则 path 中存的就是一条合法欧拉路/回路
// 4. 若图不连通或度数条件不满足, 返回 false


// 有向图欧拉路
struct DirectedEulerPath
{
    int n, m;
    vector<vector<int>> g;
    vector<int> din, dout, cur, path;

    DirectedEulerPath() {}
    DirectedEulerPath(int n_)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        m = 0;
        g.assign(n + 1, vector<int>());
        din.assign(n + 1, 0);
        dout.assign(n + 1, 0);
        cur.assign(n + 1, 0);
        path.clear();
    }

    void addEdge(int u, int v)
    {
        g[u].push_back(v);
        dout[u]++;
        din[v]++;
        m++;
    }

    void dfs(int u)
    {
        while(cur[u] < (int)g[u].size())
        {
            int v = g[u][cur[u]];
            cur[u]++;
            dfs(v);
        }
        path.push_back(u);
    }

    bool work()
    {
        path.clear();
        fill(cur.begin(), cur.end(), 0);

        int st = 0;
        int cnt1 = 0, cnt2 = 0;

        for(int i = 1; i <= n; i++)
        {
            if(dout[i] - din[i] == 1) st = i, cnt1++;
            else if(din[i] - dout[i] == 1) cnt2++;
            else if(din[i] != dout[i]) return false;
        }

        if(!((cnt1 == 1 && cnt2 == 1) || (cnt1 == 0 && cnt2 == 0))) return false;

        if(st == 0)
        {
            for(int i = 1; i <= n; i++)
            {
                if(dout[i] > 0)
                {
                    st = i;
                    break;
                }
            }
        }

        if(st == 0)
        {
            path = {1};
            return true;
        }

        dfs(st);
        reverse(path.begin(), path.end());
        return (int)path.size() == m + 1;
    }
};


// 无向图欧拉路
struct UndirectedEulerPath
{
    struct Edge
    {
        int to, id;
    };

    int n, m, idx;
    vector<vector<Edge>> g;
    vector<int> deg, cur, path;
    vector<int> vis;

    UndirectedEulerPath() {}
    UndirectedEulerPath(int n_)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        m = 0;
        idx = 0;
        g.assign(n + 1, vector<Edge>());
        deg.assign(n + 1, 0);
        cur.assign(n + 1, 0);
        path.clear();
        vis.clear();
    }

    void addEdge(int u, int v)
    {
        g[u].push_back({v, idx});
        g[v].push_back({u, idx ^ 1});
        deg[u]++;
        deg[v]++;
        idx += 2;
        m++;
    }

    void dfs(int u)
    {
        while(cur[u] < (int)g[u].size())
        {
            auto [v, id] = g[u][cur[u]];
            cur[u]++;
            if(vis[id]) continue;
            vis[id] = vis[id ^ 1] = 1;
            dfs(v);
        }
        path.push_back(u);
    }

    bool work()
    {
        path.clear();
        fill(cur.begin(), cur.end(), 0);
        vis.assign(idx, 0);

        int st = 0;
        int odd = 0;

        for(int i = 1; i <= n; i++)
        {
            if(deg[i] & 1)
            {
                odd++;
                st = i;
            }
        }

        if(odd != 0 && odd != 2) return false;

        if(st == 0)
        {
            for(int i = 1; i <= n; i++)
            {
                if(deg[i] > 0)
                {
                    st = i;
                    break;
                }
            }
        }

        if(st == 0)
        {
            path = {1};
            return true;
        }

        dfs(st);
        reverse(path.begin(), path.end());
        return (int)path.size() == m + 1;
    }
};

/*
使用示例:

1. 有向图
DirectedEulerPath ep(n);
for(...)
{
    int u, v;
    cin >> u >> v;
    ep.addEdge(u, v);
}
if(ep.work())
{
    for(auto x : ep.path) cout << x << " ";
    cout << "\n";
}

2. 无向图
UndirectedEulerPath ep(n);
for(...)
{
    int u, v;
    cin >> u >> v;
    ep.addEdge(u, v);
}
if(ep.work())
{
    for(auto x : ep.path) cout << x << " ";
    cout << "\n";
}

判定条件总结:

1. 无向图存在欧拉回路:
   所有非零度点连通, 且奇度点个数为 0

2. 无向图存在欧拉路:
   所有非零度点连通, 且奇度点个数为 0 或 2

3. 有向图存在欧拉回路:
   所有非零度点在忽略方向后连通, 且每个点入度等于出度

4. 有向图存在欧拉路:
   所有非零度点在忽略方向后连通, 且:
   - 恰有一个点 dout - din = 1
   - 恰有一个点 din - dout = 1
   - 其他点入度等于出度
*/