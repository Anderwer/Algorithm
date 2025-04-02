#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
int dx[4] = {0, -1, 0, 1};
int dy[4] = {-1, 0, 1, 0};  //[西, 北, 东, 南] [1, 2, 4, 8]

int n, m, cur;
int g[60][60];
int vis[60][60];
int cnt[3000];

void dfs(int x, int y)
{
    vis[x][y] = cur;
    for(int i = 0; i < 4; i++)
    {
        int xx = x + dx[i], yy = y + dy[i];
        if(xx < 0 || xx >= m || yy < 0 || yy >= n || vis[xx][yy]) continue; //越界或者已经访问过了
        if(((g[x][y] >> i) & 1) == 1) continue; //该方向有墙
        dfs(xx, yy);
    }
}

void solve()    
{
    cin >> m >> n;
    for(int i = 0; i < m; i ++)
		for(int j = 0; j < n; j ++) cin >> g[i][j];

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(vis[i][j]) continue;
            cur++;
            dfs(i, j);
        }
    }

    
    for(int i = 0; i < m; i++) for(int j = 0; j < n; j++) cnt[vis[i][j]]++;
    int Max = 0;
    for(auto x : cnt) Max = max(Max, x);
    cout << cur << "\n";
    cout << Max << "\n";
}   

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    solve();
    return 0;
}