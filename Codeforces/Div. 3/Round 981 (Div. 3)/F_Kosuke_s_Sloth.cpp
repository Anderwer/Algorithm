#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const i64 mod = 1e9 + 7;
const int N = 1e6 + 10;
i64 f[N];

void solve()
{

    i64 n, k;
    cin >> n >> k;
    f[1] = f[2] = 1;
    i64 now = 0;
    if(k == 1)
    {
        cout << n % mod << "\n";
        return;
    }
    for(int i = 3; i < N; i++)
    {
        f[i] = (f[i - 1] + f[i - 2]) % k;
        if(f[i] == 0)
        {
            now = i;
            break;
        }
    }
    cout << ((n % mod) * (now % mod)) % mod << "\n";
}
int main()
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

/*
在斐波那契数列中第 n 个能被 k 整除的数是什么
*/