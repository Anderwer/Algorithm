#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n, m;
    cin >> n >> m;
    if(m == n) cout << "Yes\n";
    else
    {
        if(m == 0 || n == 0) cout << "No\n";
        else cout << "Yes\n";
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--) solve();
    return 0;
}
