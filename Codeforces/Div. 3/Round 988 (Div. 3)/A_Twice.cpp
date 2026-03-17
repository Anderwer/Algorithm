#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1, 0);
    for(int i = 1; i <= n; i++)
    {
        int x; cin >> x;
        a[x]++;
    }
    int ans = 0;
    for(int i = 1; i <= n; i++) ans += a[i] / 2;
    cout << ans << '\n';
    
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
