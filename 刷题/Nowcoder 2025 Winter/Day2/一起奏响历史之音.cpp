#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n = 7;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++)
    {
        if(a[i] != 1 && a[i] != 2 && a[i] != 3 && a[i] != 5 && a[i] != 6)
        {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
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
