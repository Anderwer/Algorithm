#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

struct Matrix
{
    int n, mod;
    vector<int> a;

    Matrix() {}
    Matrix(int n_, int mod_, bool id = false)
    {
        n = n_;
        mod = mod_;
        a.assign(n * n, 0);
        if(id)
        {
            for(int i = 0; i < n; i++) a[i * n + i] = 1 % mod;
        }
    }

    int* operator [](int x)
    {
        return &a[x * n];
    }

    const int* operator [](int x) const
    {
        return &a[x * n];
    }
};

Matrix mul(const Matrix& A, const Matrix& B)
{
    int n = A.n, mod = A.mod;
    Matrix BT(n, mod), C(n, mod);
    for(int i = 0; i < n; i++)
    {
        const int* p = B[i];
        for(int j = 0; j < n; j++) BT[j][i] = p[j];
    }

    for(int i = 0; i < n; i++)
    {
        const int* x = A[i];
        for(int j = 0; j < n; j++)
        {
            const int* y = BT[j];
            __int128 sum = 0;
            for(int k = 0; k < n; k++) sum += (__int128)x[k] * y[k];
            C[i][j] = (int)(sum % mod);
        }
    }
    return C;
}

vector<int> mul(const Matrix& A, const vector<int>& v)
{
    int n = A.n, mod = A.mod;
    vector<int> res(n, 0);
    for(int i = 0; i < n; i++)
    {
        const int* p = A[i];
        __int128 sum = 0;
        for(int j = 0; j < n; j++) sum += (__int128)p[j] * v[j];
        res[i] = (int)(sum % mod);
    }
    return res;
}

void solve()
{
    i64 n;
    int m, mod;
    cin >> n >> m >> mod;

    int S = 2 * m + 2;
    int T = 0;
    int Ans = S - 1;

    auto idA = [&](int x)
    {
        return x;
    };
    auto idB = [&](int y)
    {
        return m + y;
    };

    Matrix M(S, mod);

    i64 c = 1LL * m * (m + 1) / 2;
    M[T][T] = c % mod;
    for(int x = 1; x <= m; x++) M[T][idA(x)] = (mod - (m - x + 1) % mod) % mod;
    for(int y = 1; y <= m; y++) M[T][idB(y)] = (mod - y % mod) % mod;

    for(int x = 1; x <= m; x++)
    {
        i64 now = 1LL * (x - 1) * x / 2;
        M[idA(x)][T] = now % mod;
        for(int u = 1; u < x; u++) M[idA(x)][idA(u)] = (mod - (x - u) % mod) % mod;
        for(int v = 1; v < x; v++) M[idA(x)][idB(v)] = (mod - v % mod) % mod;
    }

    for(int y = 1; y <= m; y++)
    {
        i64 now = 1LL * (m - y) * (m - y + 1) / 2;
        M[idB(y)][T] = now % mod;
        for(int u = y + 1; u <= m; u++) M[idB(y)][idA(u)] = (mod - (m - u + 1) % mod) % mod;
        for(int v = y + 1; v <= m; v++) M[idB(y)][idB(v)] = (mod - (v - y) % mod) % mod;
    }

    for(int j = 0; j < S; j++) M[Ans][j] = M[T][j];
    M[Ans][Ans] = 1 % mod;

    vector<int> f(S, 0);
    f[T] = m % mod;
    for(int x = 1; x <= m; x++) f[idA(x)] = (x - 1) % mod;
    for(int y = 1; y <= m; y++) f[idB(y)] = 0;
    f[Ans] = m % mod;

    i64 b = n - 1;
    while(b)
    {
        if(b & 1) f = mul(M, f);
        b >>= 1;
        if(b) M = mul(M, M);
    }

    cout << f[Ans] << "\n";
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