#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<char>> a(n + 1, vector<char>(m + 1, '0'));
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) cin >> a[i][j];

    int ans = 1E9 + 10;
    vector<vector<bool>> vis(n + 1, vector<bool>(m + 1, false));
    vector<vector<bool>> visZero(n + 1, vector<bool>(m + 1, false));
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            if(a[i][j] == '1' && vis[i][j] == false)
            {
                vector<array<int, 2>> Zero;
                vis[i][j] = true;
                queue<array<int, 2>> q;
                q.push({i, j});
                while(!q.empty())
                {
                    auto [x, y] = q.front();
                    q.pop();
                    for(int k = 0; k < 4; k++)
                    {
                        int xx = x + dx[k];
                        int yy = y + dy[k];
                        if(xx < 1 || xx > n || yy < 1 || yy > m || vis[xx][yy]) continue;
                        if(a[xx][yy] == '0' && visZero[xx][yy] == false)
                        {
                            Zero.push_back({xx, yy});
                            visZero[xx][yy] = true;
                        }
                        else if(a[xx][yy] == '1')
                        {
                            q.push({xx, yy});
                            vis[xx][yy] = true;
                        }
                    }
                }
                ans = min(ans, (int)Zero.size());
                for(auto [xx, yy] : Zero) visZero[xx][yy] = false;
            }
        }
    }
    
    cout << ans << "\n";
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
