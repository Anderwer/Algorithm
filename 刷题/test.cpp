#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;

    unordered_map<string, int> vis;
    vector<string> a(n + 1);
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i];
        vis[a[i]] = 1;
    }
    
    int ans = 0;
    for(int i = 1; i <= n; i++)
    {
        int len = a[i].size();
        for(int j = 1; j < len; j++)
        {
            string pre = a[i].substr(0, j);
            string suf = a[i].substr(j);
            cout << pre << " " << suf << "\n";
            if(vis.count(pre) && vis.count(suf)) ans++;
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