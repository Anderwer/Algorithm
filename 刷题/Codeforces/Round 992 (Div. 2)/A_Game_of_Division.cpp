#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    vector<bool> flag(n + 1, true);
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            if(j == i) continue;
            if(abs(a[i] - a[j]) % k == 0) flag[i] = false;
        }
    }
    for(int i = 1; i <= n; i++)
    {
        if(flag[i] == true)
        {
            cout << "YES\n" << i << "\n";
            return;
        }
    }
    cout << "NO\n";
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
