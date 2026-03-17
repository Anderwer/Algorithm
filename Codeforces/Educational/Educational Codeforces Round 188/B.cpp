#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1), last(n + 1);
    int mx = 0, pos = 0;
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i];
        if(a[i] > mx)
        {
            mx = a[i];
            pos = i;
        }
        else if(a[i] == mx) pos = i;
        last[i] = pos;
    }

    int ans = 0;
    for(int i = n; i > 0; i = last[i] - 1) ans++;
    cout << ans << "\n";
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
