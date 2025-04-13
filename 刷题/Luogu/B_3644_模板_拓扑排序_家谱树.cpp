#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

struct ToopSort
{
    int n;
    vector<vector<int>> g;
    vector<int> tp;
    vector<int> din;

    ToopSort() {};
    ToopSort(int n_)
    {
        n = n_;
        g = vector<vector<int>>(n + 1);
        din = vector<int>(n + 1, 0);
    }

    void add(int u, int v)
    {
        g[u].push_back(v);
        din[v]++;
    }

    bool toopsort()
    {
        queue<int> q;
        for(int i = 1; i <= n; i++)
            if(din[i] == 0) q.push(i);

        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            tp.push_back(u);
            for(auto v : g[u]) 
                if(--din[v] == 0) q.push(v);
        }
        return tp.size() == n;
    }
};

void solve()
{
    int n;
    cin >> n;

    ToopSort T(n);
    for(int u = 1; u <= n; u++)
    {
        int v;
        while(cin >> v && v != 0) T.add(u, v);
    }
    T.toopsort();
    for(auto v : T.tp) cout << v << " ";
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
