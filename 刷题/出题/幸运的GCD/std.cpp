#include <bits/stdc++.h>
#define int long long
using i64 = long long;
using namespace std;
const int p = 1e9 + 7;

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
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 2, 0);
    vector<int> b(n + 2, 0);

    for(int i = 1; i <= m; i++)
    {
        int L, R, q;
        cin >> L >> R >> q;
        if(q == 3)
        {
            a[L]++;
            a[R + 1]--;
        }
        else
        {
            b[L]++;
            b[R + 1]--;
        }
    }
    int a_min = 1e9, b_min = 1e9;
    for(int i = 1; i <= n; i++)
    {
        a[i] += a[i - 1];
        b[i] += b[i - 1];
        a_min = min(a_min, a[i]);
        b_min = min(b_min, b[i]);
    }
    
    cout << qpow(3, a_min) * qpow(5, b_min) % p << "\n";
}

signed main()
{
    //std::ios::sync_with_stdio(false);
    //std::cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
