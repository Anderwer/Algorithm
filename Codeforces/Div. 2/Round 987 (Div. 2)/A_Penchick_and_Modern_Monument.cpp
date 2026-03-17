#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<int> cnt(n + 1);
    for(int i = 1; i <= n; i++)
    {
        int x; cin >> x;
        cnt[x]++;
    }
    int Max = 0;
    for(int i = 1; i <= n; i++) Max = max(Max, cnt[i]);
    cout << n - Max << "\n";
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
