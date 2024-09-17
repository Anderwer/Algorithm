#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

const int N = 1000;
int b[N], c[N];
void solve()
{
    int n, pos;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> b[i], c[i] = b[i];
    sort(b + 1, b + 1 + n);
    sort(c + 1, c + 1 + n, greater<int>());
    cin >> pos;
    cout << c[upper_bound(c + 1, c + 1 + n, pos, greater<int>()) - c] << " " << b[upper_bound(b + 1, b + 1 + n, pos) - b];
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
