#include <bits/stdc++.h>
#define int long long
using i64 = long long;
using namespace std;
const int inf = 1e18;
const int dx[4] = {0, 1, 0, -1};  
const int dy[4] = {1, 0, -1, 0};

struct node
{
    int x, y, cur;
    i64 t;
    bool operator>(const node& a) const
    {
        return t > a.t;
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<i64>> t(n + 1, vector<i64>(m + 1));
    vector<vector<i64>> d(n + 1, vector<i64>(m + 1));
    
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) cin >> t[i][j];
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) cin >> d[i][j];

    vector<vector<vector<i64>>> dist(n + 1, vector<vector<i64>>(m + 1, vector<i64>(4, inf)));
    priority_queue<node, vector<node>, greater<node>> pq;
    dist[0][0][0] = 0;
    pq.push({0, 0, 0, 0});
    i64 ans = inf;
    while(!pq.empty())
    {
        auto now = pq.top();
        pq.pop();
        if(now.t > dist[now.x][now.y][now.cur]) continue;
        if(now.x == n - 1 && now.y == m - 1)
        {
            int down = 1;
            i64 cost;
            if(now.cur != down) cost = t[now.x][now.y] + d[now.x][now.y];
            else cost = t[now.x][now.y];
            ans = min(ans, now.t + cost);
            continue;
        }

        for(int i = 0; i < 4; i++)
        {
            int xx = now.x + dx[i];
            int yy = now.y + dy[i];
            if(xx < 0 || xx >= n || yy < 0 || yy >= m) continue;
            i64 cost;
            if(now.cur != i) cost = t[now.x][now.y] + d[now.x][now.y];
            else cost = t[now.x][now.y];

            i64 time = now.t + cost;
            if(time < dist[xx][yy][i])
            {
                dist[xx][yy][i] = time;
                pq.push({xx, yy, i, time});
            }
        }
    }

    cout << ans << "\n";
}

signed main()
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
