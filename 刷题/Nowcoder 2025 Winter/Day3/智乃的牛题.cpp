#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    string s;
    cin >> s;
    map<char, int> mp;
    for(auto v : s) mp[v]++;
    if(mp['n'] == 1 && mp['o'] == 2 && mp['w'] == 1 && mp['c'] == 1 && mp['d'] == 1 && mp['e'] == 1 && mp['r'] == 1)
    {
        cout << "happy new year\n";
    }
    else cout << "I AK IOI\n";
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
