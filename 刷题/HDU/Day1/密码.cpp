#include <bits/stdc++.h>
using i64 = long long;
using namespace std;


int ans, n;
void check(int a, int b, int c, unordered_map<int, int>& mp)
{
    if((c - b) % a == 0)
    {
        int x = (c - b) / a;
        if(x < 0) return;
        mp[x]++;
        if(mp[x] == n) ans = x;
    }
    
}

void solve()
{
    cin >> n;
    unordered_map<int, int> mp;
    ans = 0;
    
    for(int i = 1; i <= n; i++) 
    {
        int u, v, w;
        cin >> u >> v >> w;

        int a = u, b = v, c = w;
        check(a, b, c, mp);
        check(a, c, b, mp);
        check(b, a, c, mp);
        check(b, c, a, mp);
        check(c, a, b, mp);
        check(c, b, a, mp);
    }
    cout << ans << "\n";
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
