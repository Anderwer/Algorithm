#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int mod = 998244353;

i64 qpow(i64 a, i64 b)
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
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1), k(m + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= m; i++) cin >> k[i];

    i64 base = 0;
    for(int i = 1; i <= n; i++)
    {
        base = (base + 1LL * i * (n - i + 1) % mod * qpow(a[i], mod - 2)) % mod;
    }

    vector<int> L(n + 1), R(n + 1), st;
    for(int i = 1; i <= n; i++)
    {
        while(!st.empty() && a[st.back()] >= a[i]) st.pop_back();
        L[i] = st.empty() ? 0 : st.back();
        st.push_back(i);
    }

    st.clear();
    for(int i = n; i >= 1; i--)
    {
        while(!st.empty() && a[st.back()] > a[i]) st.pop_back();
        R[i] = st.empty() ? n + 1 : st.back();
        st.push_back(i);
    }

    vector<pair<int, i64>> b;
    {
        vector<pair<int, i64>> c;
        for(int i = 1; i <= n; i++) c.push_back({a[i], 1LL * (i - L[i]) * (R[i] - i)});
        sort(c.begin(), c.end());
        for(auto [x, y] : c)
        {
            if(b.empty() || b.back().first != x) b.push_back({x, y});
            else b.back().second += y;
        }
    }

    i64 S = 0;
    for(auto [x, y] : b) S = (S + y % mod * qpow(x, mod - 2)) % mod;

    i64 cnt = 0, sum = 0, inv = 0;
    int p = 0;
    for(int i = 1; i <= m; i++)
    {
        while(p < (int)b.size() && b[p].first <= k[i] + 1)
        {
            auto [x, y] = b[p];
            y %= mod;
            cnt = (cnt + y) % mod;
            sum = (sum + y * x) % mod;
            inv = (inv + y * qpow(x, mod - 2)) % mod;
            p++;
        }

        i64 ans = base;
        ans = (ans + 1LL * k[i] % mod * S) % mod;
        ans = (ans + 1LL * (k[i] + 2) % mod * cnt) % mod;
        ans = (ans - sum + mod) % mod;
        ans = (ans - 1LL * (k[i] + 1) % mod * inv % mod + mod) % mod;
        cout << ans << "\n";
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
