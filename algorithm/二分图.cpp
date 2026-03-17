#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

// 二分图模板集合
// 包含:
// 1. 二分图判定
// 2. 二分图染色
// 3. 二分图最大匹配(Kuhn 增广路算法, 适合稀疏图 / 数据范围中等)
//
// 约定:
// 1. 点编号默认 1..n
// 2. 最大匹配模板中, 左部点编号 1..n1, 右部点编号 1..n2


// 二分图判定 + 染色
struct BipartiteGraph
{
    int n;
    vector<vector<int>> g;
    vector<int> col;

    BipartiteGraph() {}
    BipartiteGraph(int n_)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        g.assign(n + 1, {});
        col.assign(n + 1, -1);
    }

    void addEdge(int u, int v)
    {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    bool bfs(int s)
    {
        queue<int> q;
        q.push(s);
        col[s] = 0;

        while(!q.empty())
        {
            int u = q.front();
            q.pop();

            for(auto v : g[u])
            {
                if(col[v] == -1)
                {
                    col[v] = col[u] ^ 1;
                    q.push(v);
                }
                else if(col[v] == col[u]) return false;
            }
        }
        return true;
    }

    bool check()
    {
        fill(col.begin(), col.end(), -1);
        for(int i = 1; i <= n; i++)
        {
            if(col[i] == -1)
            {
                if(!bfs(i)) return false;
            }
        }
        return true;
    }

    vector<vector<int>> getParts()
    {
        vector<vector<int>> part(2);
        for(int i = 1; i <= n; i++)
        {
            if(col[i] != -1) part[col[i]].push_back(i);
        }
        return part;
    }
};


// 二分图最大匹配: Kuhn 增广路算法
// 说明:
// 1. 适用于无权二分图最大匹配
// 2. 左部点数 n1, 右部点数 n2
// 3. 时间复杂度 O(n1 * m)
struct BipartiteMatching
{
    int n1, n2;
    vector<vector<int>> g;
    vector<int> matchL, matchR, vis;

    BipartiteMatching() {}
    BipartiteMatching(int n1_, int n2_)
    {
        init(n1_, n2_);
    }

    void init(int n1_, int n2_)
    {
        n1 = n1_;
        n2 = n2_;
        g.assign(n1 + 1, {});
        matchL.assign(n1 + 1, 0);
        matchR.assign(n2 + 1, 0);
    }

    void addEdge(int u, int v)
    {
        g[u].push_back(v);
    }

    bool dfs(int u)
    {
        for(auto v : g[u])
        {
            if(vis[v]) continue;
            vis[v] = 1;

            if(matchR[v] == 0 || dfs(matchR[v]))
            {
                matchL[u] = v;
                matchR[v] = u;
                return true;
            }
        }
        return false;
    }

    int maxMatching()
    {
        int ans = 0;
        fill(matchL.begin(), matchL.end(), 0);
        fill(matchR.begin(), matchR.end(), 0);

        for(int u = 1; u <= n1; u++)
        {
            vis.assign(n2 + 1, 0);
            if(dfs(u)) ans++;
        }
        return ans;
    }
};

/*
使用方式:

1. 二分图判定
BipartiteGraph bg(n);
bg.addEdge(u, v);
bool ok = bg.check();
if(ok)
{
    auto part = bg.getParts();
}

2. 二分图最大匹配
BipartiteMatching bm(n1, n2);
bm.addEdge(u, v); // u 属于左部, v 属于右部
int ans = bm.maxMatching();

常见结论:
1. 二分图最小点覆盖 = 最大匹配
2. 二分图最大独立集 = n - 最大匹配
3. DAG 最小路径覆盖(拆点后) = 点数 - 最大匹配
*/