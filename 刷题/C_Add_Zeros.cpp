#include <bits/stdc++.h>
#define int long long
using i64 = long long;
using namespace std;
const int N = 3e5 + 10;

int a[N];
map<i64, vector<int>> mp;
map<i64, bool> vis;
int ans = 0;

void dfs(int len)
{
    vis[len] = true;
    ans = max(ans, len);
    for(auto& v : mp[len])
    {
        if(vis[len + v - 1] == false) dfs(len + v - 1LL);
    }
}

void solve()
{
    int n;
    cin >> n;
    mp.clear();
    vis.clear();
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i];
        mp[a[i] + i - 1LL].push_back(i);
    }
    ans = 0;
    dfs(n);
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
/*
先记录一下每个点所需要的长度是多少才能满足条件
len = a[i] + i - 1
然后开一个map 统计每种长度下一共有哪些点可以选
最后dfs, 找最长
*/