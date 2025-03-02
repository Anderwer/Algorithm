#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    string s;
    cin >> n >> s;
    s = " " + s;
    int ans = 0;
    vector<int> pos(30, 0);
    
    for(int i = 1; i <= n; i++)
    {
        if(pos[s[i] - 'a'] != 0) ans = max({ans, pos[s[i] - 'a'], n - i + 1});
        pos[s[i] - 'a'] = i;
    }
    cout << ans << '\n';
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
