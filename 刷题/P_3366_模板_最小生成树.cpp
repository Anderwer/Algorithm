#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

const int M = 2e5 + 10;
const int N = 1e4 + 10;
struct Edge
{
    int u, v, w;
    bool operator < (const Edge& t) {return w < t.w;}
}e[M];
int f[N], cnt, ans, n, m;

int find(int x)
{
    while(x != f[x]) x = f[x] = f[f[x]];
    return x;
}

bool kruskal()
{
    sort(e + 1, e + 1 + m);
    for(int i = 1; i <= n; i++) f[i] = i;
    for(int i = 1; i <= m; i++)
    {
        auto [u, v, w] = e[i];
        u = find(u), v = find(v);
        if(u != v)
        {
            f[u] = v;
            ans += w;
            cnt++;
        }
    }
    return cnt == n - 1;
}

void solve()
{
    cin >> n >> m;

    for(int i = 1; i <= m; i++)
    {
        int u, v, w; cin >> u >> v >> w;
        e[i] = {u, v, w};
    }
    if(kruskal()) cout << ans << "\n";
    else cout << "orz\n";
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
