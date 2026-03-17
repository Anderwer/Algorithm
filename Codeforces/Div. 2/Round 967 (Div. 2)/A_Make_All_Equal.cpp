#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    int cnt = 0;
    map<int, int> mp;
    for(int i = 1; i <= n; i++)
    {
        int x; cin >> x;
        mp[x]++;
        cnt = max(cnt, mp[x]);
    }
    cout << n - cnt << "\n";
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
