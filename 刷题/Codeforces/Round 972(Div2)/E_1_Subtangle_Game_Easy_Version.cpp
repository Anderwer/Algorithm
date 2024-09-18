#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

int l, n, m;
int a[305];
int b[305][305];
int f[305][305][305]; //dp[i][j][k] : 到第k步时,选点为(i, j)是否会win
map<int, vector<array<int, 2>>> pos;

bool dfs(int x, int y, int k)
{
    if(f[x][y][k] != -1) return f[x][y][k];
    if(k == l - 1) return true; //下到最后一步的获胜

    bool flag = true;
    for(auto &nxt : pos[a[k + 1]]) //枚举下一步选点
    {
        if(nxt[0] <= x || nxt[1] <= y) continue; //下在右下角
        if(dfs(nxt[0], nxt[1], k + 1) == true) flag = false; //如果下一步能赢,当前这步则输
    }
    f[x][y][k] = flag;
    return flag;
}

void solve()
{
    cin >> l >> n >> m;
    for(int i = 0; i < l; i++) cin >> a[i];
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++) cin >> b[i][j];

    pos.clear();
    for(int i = 0; i < n; i++)
    {
        map<int, bool> vis;
        for(int j = m - 1; j >= 0; j--)
        {
            if(!vis[b[i][j]]) vis[b[i][j]] = true, pos[b[i][j]].push_back({i, j});
        }
    }

    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            for(int k = 0; k <= l; k++) f[i][j][k] = -1;

    for(auto &nxt : pos[a[0]])
    {
        if(dfs(nxt[0], nxt[1], 0) == true)
        {
            cout << "T\n";
            return;
        }
    }
    cout << "N\n";
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
