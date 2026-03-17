#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

// 拓扑排序
// 适用范围:
// 1. 判断有向图是否有环
// 2. 求一组拓扑序
// 3. DAG 上做 DP 前的预处理

struct TopoSort
{
    int n;
    vector<vector<int>> g;
    vector<int> din;
    vector<int> order;

    TopoSort() {}
    TopoSort(int n_)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        g.assign(n + 1, vector<int>());
        din.assign(n + 1, 0);
        order.clear();
    }

    void add(int u, int v)
    {
        g[u].push_back(v);
        din[v]++;
    }

    bool sort()
    {
        queue<int> q;
        vector<int> deg = din;
        order.clear();

        for(int i = 1; i <= n; i++)
        {
            if(deg[i] == 0) q.push(i);
        }

        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            order.push_back(u);

            for(auto v : g[u])
            {
                if(--deg[v] == 0) q.push(v);
            }
        }

        return (int)order.size() == n;
    }
};