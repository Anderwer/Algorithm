#include <bits/stdc++.h>
#define int long long
using i64 = long long;
using namespace std;
const int mod = 998244353;

i64 qpow(int a, int b)
{
    i64 res = 1;
    while(b)
    {
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) cin >> b[i];

    vector<int> a_ = a;
    vector<int> b_ = b;

    sort(a_.begin() + 1, a_.end());
    sort(b_.begin() + 1, b_.end());
    i64 P = 1;
    for(int i = 1; i <= n; i++) P = P * min(a_[i], b_[i]) % mod;
    cout << P << " ";

    while(q--)
    {
        int o, x; cin >> o >> x;
        if(o == 1)
        {
            int pos = upper_bound(a_.begin() + 1, a_.end(), a[x]) - a_.begin() - 1;
            P = (i64)P * qpow(min(a_[pos], b_[pos]), mod - 2) % mod;
            a[x]++, a_[pos]++;
            P = P * min(a_[pos], b_[pos]) % mod;
            cout << P << " ";
        }
        else
        {
            int pos = upper_bound(b_.begin() + 1, b_.end(), b[x]) - b_.begin() - 1;
            P = (i64)P * qpow(min(a_[pos], b_[pos]), mod - 2) % mod;
            b[x]++, b_[pos]++;
            P = P * min(a_[pos], b_[pos]) % mod;
            cout << P << " ";
        }
    }
    cout << "\n";
}

signed main()
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
