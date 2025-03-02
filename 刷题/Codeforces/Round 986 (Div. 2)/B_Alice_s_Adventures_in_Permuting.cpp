#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    i64 n, b, c;
    cin >> n >> b >> c;
    if(c >= n) cout << n << "\n";
    else
    {
        if(b == 0)
        {
            if(n - 3 >= c) cout << -1 << "\n";
            else cout << n - 1 << "\n";
        }
        else cout << n - (n - c - 1) / b - 1 << "\n";
    }
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
