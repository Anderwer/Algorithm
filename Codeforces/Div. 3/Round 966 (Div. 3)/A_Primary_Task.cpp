#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    string s;
    cin >> s;
    bool is = true;
    if(s.size() < 3 || s.substr(0, 2) != "10" || s.substr(2, 1) == "0" || s.substr(2, s.size() - 2) == "1") is = false;
    if(is) cout << "YES\n";
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
