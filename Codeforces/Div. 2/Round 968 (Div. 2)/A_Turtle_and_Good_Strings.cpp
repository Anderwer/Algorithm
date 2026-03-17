#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
char s[110];

void solve()
{
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> s[i];
    if(s[1] == s[n]) cout << "NO\n";
    else cout << "YES\n";
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
