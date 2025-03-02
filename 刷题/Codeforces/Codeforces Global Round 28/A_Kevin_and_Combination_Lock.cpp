#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int x;
    cin >> x;
    if(x % 33 == 0) cout << "YES\n";
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
