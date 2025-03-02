#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n, m;
    cin >> n >> m;
    int ans = 0;
    bool flag = true;
    for(int i = 1; i <= n; i++)
    {
        string s; cin >> s;
        if(s.size() <= m && flag == true)
        {
            ans++;
            m -= s.size();
        }
        else flag = false;
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
