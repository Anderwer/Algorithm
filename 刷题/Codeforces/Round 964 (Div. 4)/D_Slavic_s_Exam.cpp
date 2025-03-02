#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    string s, t;
    cin >> s >> t;

    int pos = 0, len = t.size();
    for(int i = 0; i < s.size(); i++)
    {
        if(pos < len && (s[i] == t[pos] || s[i] == '?')) s[i] = t[pos], pos++;
        if(pos == len && s[i] == '?') s[i] = 'a';
    }
    if(pos == len) cout << "YES\n" << s << "\n";
    else cout << "NO\n";
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
