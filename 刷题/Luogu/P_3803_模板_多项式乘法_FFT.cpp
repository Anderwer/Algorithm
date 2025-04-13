#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

struct FFT 
{
    const double PI = acos(-1);
    int n, m, k, sm;
    vector<int> tax;
    vector<complex<double>> F, G;

    FFT() {};
    FFT(vector<int>& a, vector<int>& b) // a 和 b 都从 0 开始
    {
        n = a.size() - 1;
        m = b.size() - 1;
        k = 1;
        sm = n + m;
        while(k <= sm) k <<= 1;
        tax = vector<int>(k << 2, 0);
        F = vector<complex<double>>(k << 2, 0);
        G = vector<complex<double>>(k << 2, 0);
        for(int i = 0; i <= n; i++) F[i] = a[i];
        for(int i = 0; i <= m; i++) G[i] = b[i];
    }
    
    void fft(vector<complex<double>>& A, int N)
    {
        for(int i = 1; i < N; i++)
            if(tax[i] > i) swap(A[i], A[tax[i]]);

        for(int len = 2, M = 1; len <= N; M = len, len <<= 1)
        {   
            complex<double> I(cos(PI / M), sin(PI / M)), w(1.0, 0.0);
            for(auto L = 0, R = len - 1; R <= N; L += len, R += len)
            {
                auto w0 = w;
                for(auto p = L, lim = L + M; p < lim; p++)
                {
                    auto x = A[p] + w0 * A[p + M];
                    auto y = A[p] - w0 * A[p + M];
                    A[p] = x, A[p + M] = y;
                    w0 *= I;
                }
            }
        }
    }
    
    void makeRev(int N)
    {
        int d = N >> 1, p = 0;
        tax[p++] = 0;
        tax[p++] = d;
        for(int w = 2; w <= N; w <<= 1)
        {
            d >>= 1;
            for(int p0 = 0; p0 < w; p0++)
                tax[p++] = tax[p0] | d;
        }
    }

    vector<int> mul()
    {
        makeRev(k);
        fft(F, k);
        fft(G, k);
        for(int i = 0; i < k; i++) F[i] *= G[i];
        fft(F, k);
        reverse(F.begin() + 1, F.begin() + k);
        
        vector<int> c(sm + 1);
        for(int i = 0; i <= sm; i++) c[i] = int(F[i].real() / k + 0.5);
        return c;
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1), b(m + 1);
    for(int i = 0; i <= n; i++) cin >> a[i];
    for(int i = 0; i <= m; i++) cin >> b[i];

    FFT F(a, b);
    vector<int> c = F.mul();
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
