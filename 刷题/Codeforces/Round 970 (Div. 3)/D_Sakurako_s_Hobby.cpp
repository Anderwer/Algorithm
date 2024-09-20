#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

const int N = 2e5 + 10;
int n;
int p[N];
char col[N];
int f[N];
bool vis[N];
void solve()
{
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> p[i], f[i] = 0, vis[i] = false;
    for(int i = 1; i <= n; i++) cin >> col[i];
    map<int, vector<int>> mp;
    int cnt = 0;
    for(int i = 1; i <= n; i++)
    {
        if(vis[i]) continue;
        vis[i] = true;
        mp[++cnt].push_back(i);
        int next = p[i];
        while(vis[next] == false)
        {
            vis[next] = true;
            mp[cnt].push_back(next);
            next = p[next];
        }
    }
    for(int i = 1; i <= cnt; i++)
    {
        int num = 0;
        for(auto &v : mp[i]) if(col[v] == '0') num++;
        for(auto &v : mp[i]) f[v] = num;
    }
    for(int i = 1; i <= n; i++) cout << f[i] << " ";
    cout << "\n";

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
    
*/