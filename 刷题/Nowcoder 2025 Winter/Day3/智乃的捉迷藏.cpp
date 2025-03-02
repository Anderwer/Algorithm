#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n, a, b, c;
    cin >> n >> a >> b >> c;
    int y = a + b + c - n;
    if(y >= 0 && y <= n) cout << "Yes\n";
    else cout << "No\n";
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
