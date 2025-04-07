#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int p = 998244353;
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

void solve()
{
    i64 n;
    cin >> n;
    
    i64 r = n % 5, ans = 0;
    if(r == 0 || r == 2) ans = 1;
    else if(r == 1)
    {
        i64 x = (n - 1) / 5;
        if(x == 0) ans = qpow(2, p - 2);
        else ans = (1 - qpow(2, p - 1 - x) + p) % p;
    }
    else if(r == 3)
    {
        i64 x = (n - 3) / 5;
        ans = (1 - qpow(2, p - 3 - x) + p) % p;
    }
    else if(r == 4)
    {
        i64 x = (n - 4) / 5;
        ans = (1 - qpow(2, p - 2 - x) + p) % p;
    }
    cout << ans << "\n";
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
