#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int p = 998244353;
i64 n, m;

i64 qpow(i64 a, i64 b)
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

vector<i64> pmul(vector<i64>& a, vector<i64>& b) 
{
    vector<i64> res(m, 0);
    for (int i = 0; i < m; i++) 
    {
        if(a[i] == 0) continue;
        for (int j = 0; j < m; j++)
            res[(i + j) % m] = (res[(i + j) % m] + a[i] * b[j] ) % p;
    }
    return res;
}

vector<i64> ppow(vector<i64> base, i64 x)
{
    vector<i64> res(m, 0);
    res[0] = 1;
    while(x > 0) 
    {
        if(x & 1)
            res = pmul(res, base);
        base = pmul(base, base);
        x >>= 1;
    }
    return res;
}

void solve()
{
    cin >> n >> m;
    i64 q = n / m;
    i64 rem = n % m;

    vector<i64> cnt(m, 0);
    cnt[0] = q;
    for(int i = 1; i < m; i++)
    {
        if(i <= rem) cnt[i] = q + 1;
        else cnt[i] = q;
    }

    vector<vector<i64>> f(m, vector<i64>(m, 0));
    f[0][0] = qpow(2, cnt[0]);

    for(int i = 1; i < m; i++)
    {
        vector<i64> base(m, 0);
        base[0] = 1;
        base[i % m] = (base[i % m] + 1) % p;
        f[i] = ppow(base, cnt[i]);
    }

    vector<i64> res(m, 0);
    res[0] = 1;
    for(int i = 0; i < m; i++) res = pmul(res, f[i]);

    i64 ans = res[0] - 1;
    cout << (ans + p) % p << "\n";
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--)
    {
        solve();
    }
    return 0;
}
