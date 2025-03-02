#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    i64 n;
    cin >> n;
    if(n == 1) cout << "Yes\n";
    else
    {
        if(n & 1) cout << "Yes\n";
        else cout << "No\n";
    }
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
