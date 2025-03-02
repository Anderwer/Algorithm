#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 2E5 + 10;

void solve()
{
    int n;
    cin >> n;
    vector<int> cnt(N + 1, 0);
    for(int i = 1; i <= n; i++)
    {
        int x; cin >> x;
        cnt[x]++;
    }
    i64 ans = 0;
    for(int g = 1; g < N; g++)
    {
        for(int i = g * 2; i < N; i += g)
        {
            if((i ^ (i - g)) == g) ans += 1LL * cnt[i] * cnt[i - g];
        }
    }
    cout << ans << '\n';
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
