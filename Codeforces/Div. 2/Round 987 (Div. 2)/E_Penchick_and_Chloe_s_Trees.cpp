#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void dfs(int u, vector<vector<int>>& g, vector<int>& f)
{
    priority_queue<int, vector<int>, greater<int>> pq;
    for(auto v : g[u])
    {
        dfs(v, g, f);
        pq.push(f[v]);
    }
    while(pq.size() > 2)
    {
        int x = pq.top();
        pq.pop();
        int y = pq.top();
        pq.pop();
        pq.push(max(x, y) + 1);
    }
    if(pq.empty()) f[u] = 0;
    else if(pq.size() == 1) f[u] = pq.top() + 1;
    else
    {
        int x = pq.top();
        pq.pop();
        int y = pq.top();
        pq.pop();
        f[u] = max(x, y) + 1;
    }
}

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> g(n + 1);
    for(int i = 2; i <= n; i++)
    {
        int x; cin >> x;
        g[x].push_back(i);
    }

    vector<int> f(n + 1, 0);
    dfs(1, g, f);
    cout << f[1] << "\n";
}

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

/*
正难则反, 题目要求把一个深度为 d 的满二叉树通过删点变成给定的树, 这样考虑比较复杂
反过来想, 把给定的树变成一颗满二叉树需要添加多少个点

设 f[x] 为 以 x 为根节点的子树变成一棵满二叉树时所需要的最小深度
转移时, 每次选两个 x 的儿子 v1, v2, 然后再向上合成为一个儿子, 其所需深度为 max(f[v1], f[v2]) + 1, 然后再加入 x 的儿子中
根据上述模拟, 容易想到优先队列维护, 当队列中只剩 1 个儿子时, 这个值即为 f[x]
要使深度最小, 根据贪心, 我们每次选最小的两个儿子进行合并, 维护小根堆即可
*/