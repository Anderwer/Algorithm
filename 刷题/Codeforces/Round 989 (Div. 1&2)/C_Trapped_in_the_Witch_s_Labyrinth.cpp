#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
vector<int> dx = {1, 0, -1, 0}; // 下, 右, 上, 左
vector<int> dy = {0, 1, 0, -1};

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<char>> a(n + 1, vector<char>(m + 1, '#'));
    vector<array<int, 2>> point;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            cin >> a[i][j];
            if(a[i][j] == 'U' && i == 1) point.push_back({i, j});
            if(a[i][j] == 'L' && j == 1) point.push_back({i, j});
            if(a[i][j] == 'R' && j == m) point.push_back({i, j});
            if(a[i][j] == 'D' && i == n) point.push_back({i, j});
        }
    }
    if(n == 1 && m == 1)
    {
        cout << 0 << "\n";
        return;
    }
    if(point.empty())
    {
        cout << n * m << "\n";
        return;
    }
    vector<vector<bool>> vis(n + 1, vector<bool>(m + 1, false));
    vector<vector<int>> mark(n + 1, vector<int>(m + 1, 0));

    queue<array<int, 2>> q;
    for(auto x : point) q.push(x);
    while(!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();
        vis[x][y] = true;
        mark[x][y] = 1;
        for(int k = 0; k < 4; k++)
        {
            int xx = x + dx[k], yy = y + dy[k];
            if(xx < 1 || xx > n || yy < 1 || yy > m || vis[xx][yy] || a[xx][yy] == '?') continue;
            if(k == 0 && a[xx][yy] == 'U') q.push({xx, yy});
            if(k == 1 && a[xx][yy] == 'L') q.push({xx, yy});
            if(k == 2 && a[xx][yy] == 'D') q.push({xx, yy});
            if(k == 3 && a[xx][yy] == 'R') q.push({xx, yy});
        }
    }
    int ans = 0;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            if(a[i][j] != '?')
            {
                if(mark[i][j] == 0) ans++;
                continue;
            }
            bool flag = false;
            for(int k = 0; k < 4; k++)
            {
                int x = i + dx[k];
                int y = j + dy[k];
                if(x < 1 || x > n || y < 1 || y > m) continue;
                if(mark[x][y] == 0) flag = true;
            }
            ans += flag;
        }
    }
    cout << ans << "\n";
    /*
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++) cout << mark[i][j];
        cout << "\n";
    }
    */
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
