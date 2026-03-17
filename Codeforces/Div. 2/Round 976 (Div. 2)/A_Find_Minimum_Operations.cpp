#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

int get(int a, int b)
{
    int res = log10(a) / log10(b);
    return res;
}

void solve()
{
    int n, k;
    cin >> n >> k;
    if(k == 1)
    {
        cout << n << "\n";
    }
    else
    {
        int cnt = 0;
        while(n > 0)
        {
            int x = get(n, k);
            int now = pow(k, x);
            cnt += (n / now);
            n = n - (n / now) * now;
        }
        cout << cnt << "\n";
    }
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
100 - 81 = 19

*/