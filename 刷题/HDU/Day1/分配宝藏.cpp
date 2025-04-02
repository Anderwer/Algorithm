#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int p = 1e9 + 7;

void solve()
{
    i64 n;
    cin >> n;
    if(n & 1) n--;
    n /= 2;
    cout << n * (n + 1) % p << "\n";
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
