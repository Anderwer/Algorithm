#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    string s;
    cin >> s;
    string ans;
    int r = s.size();
    for(int i = 0; i < r; i++)
    {
        if(i + 2 < r && s[i] != s[i + 1] && s[i] != s[i + 2] && s[i + 1] != s[i + 2])
        {
            ans += s[i];
            ans += s[i + 1];
            ans += s[i + 2];
            break;
        }
        if(i + 1 < r && s[i] == s[i + 1])
        {
            ans += s[i];
            ans += s[i + 1];
            break;
        }
    }
    if(ans.empty()) cout << -1 << "\n";
    else cout << ans << "\n";
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
