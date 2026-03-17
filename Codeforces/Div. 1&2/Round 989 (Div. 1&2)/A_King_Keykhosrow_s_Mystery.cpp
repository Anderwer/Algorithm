#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int a, b;
    cin >> a >> b;
    cout << lcm(a, b) << "\n";
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
