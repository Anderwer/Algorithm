#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int p = 998244353;

struct NTT
{
    const int G_ = 3, Gi = 332748118;
    int n, m, sm, k, cnt;
    vector<int> tax;
    vector<i64> F, G;

    NTT() {};
    NTT(vector<i64>& a, vector<i64>& b)
    {
        n = a.size() - 1;
        m = b.size() - 1;
        sm = n + m;
        k = 1;
        cnt = 0;
        while(k <= sm) k <<= 1, cnt++;
        tax = vector<int>(k + 10, 0);
        F = vector<i64>(k + 10, 0);
        G = vector<i64>(k + 10, 0);

        for(int i = 0; i <= n; i++) F[i] = a[i] % p;
        for(int i = 0; i <= m; i++) G[i] = b[i] % p;
        for(int i = 0; i < k; i++)
            tax[i] = (tax[i >> 1] >> 1) | ((i & 1) << (cnt - 1));
    }

    inline i64 qpow(i64 a, i64 b)
    {
        i64 res = 1;
        while(b)
        {
            if(b & 1) res = res * a % p;
            a = a * a % p;
            b >>= 1;
        }
        return res;
    }

    void ntt(vector<i64>& A, int type)
    {
        for(int i = 0; i < k; i++)
            if(tax[i] > i) swap(A[i], A[tax[i]]);

        for(int mid = 1; mid < k; mid <<= 1)
        {
            i64 Wn = qpow(type == 1 ? G_ : Gi, (p - 1) / (mid << 1));
            for(int j = 0; j < k; j += (mid << 1))
            {
                i64 w = 1;
                for(int L = 0; L < mid; L++, w = (w * Wn) % p)
                {
                    i64 x = A[j + L];
                    i64 y = w * A[j + L + mid] % p;
                    A[j + L] = (x + y) % p;
                    A[j + L + mid] = (x - y + p) % p;
                }
            }
        }

        if(type == -1)
        {
            i64 inv = qpow(k, p - 2);
            for(int i = 0; i <= sm; i++) A[i] = (A[i] * inv) % p;
        }
    }

    vector<i64> mul()
    {
        vector<i64> c(sm + 1);
        ntt(F, 1);
        ntt(G, 1);
        for(int i = 0; i < k; i++) F[i] = (F[i] * G[i]) % p;
        ntt(F, -1);
        for(int i = 0; i <= sm; i++) c[i] = F[i];
        return c;
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<i64> a(n + 1), b(m + 1);
    for(int i = 0; i <= n; i++) cin >> a[i];
    for(int i = 0; i <= m; i++) cin >> b[i];
    
    NTT ntt(a, b);
    vector<i64> c = ntt.mul();
    for(auto v : c) cout << v << " ";
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    //cin >> t;
    while(t--)
    {
        solve();
    }
    return 0;
}
