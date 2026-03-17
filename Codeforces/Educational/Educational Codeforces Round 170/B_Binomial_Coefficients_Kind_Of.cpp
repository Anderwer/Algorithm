#include <bits/stdc++.h>
#define int long long
using i64 = long long;
using namespace std;
const int N = 1e5 + 10;
const int p = 1e9 + 7;

int a[N], b[N];

int qpow(int a, int b)
{
    int res = 1;
    while(b)
    {
        if(b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

void solve()
{
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) cin >> b[i];

    for(int i = 1; i <= n; i++) cout << qpow(2, b[i]) << "\n";
}
signed main()
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
/*
C[n][k] = C[n][k - 1] + C[n - 1][k - 1]
打表
*/