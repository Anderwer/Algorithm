#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

void solve()
{
    int n, k;
    cin >> n >> k;
    int L = n - k + 1;
    int R = n;
    int odd = 0;
    if(L % 2 == 0 && R % 2 == 0) odd = (R - L - 1) / 2 + 1;
    else if(L % 2 == 1 && R % 2 == 1) odd = (R - L - 1) / 2 + 2;
    else odd = (R - L - 1) / 2 + 1;
    if(odd & 1) cout << "NO\n";
    else cout << "YES\n";
}

int main() 
{
    int t = 1;
    cin >> t;
    while(t--) solve();
    return 0;
}