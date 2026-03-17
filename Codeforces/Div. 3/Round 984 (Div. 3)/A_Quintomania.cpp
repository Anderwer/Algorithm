#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
int a[100];

void solve()
{
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    bool is_ok = true;
    for(int i = 1; i < n; i++)
        if(abs(a[i] - a[i + 1]) != 5 && abs(a[i] - a[i + 1]) != 7) is_ok = false;
    if(is_ok) cout << "YES\n";
    else cout << "NO\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t = 1;
    cin >> t;
    while(t--) solve();
    return 0;
}