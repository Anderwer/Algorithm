#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    i64 n, x;
    cin >> n >> x;
    i64 ans = 0;
    for(i64 a = 1; a <= x; a++)
    {
        for(i64 b = 1; a + b < x && a * b + a + b <= n; b++)
        {
            ans += min(x - (a + b), (n - a * b) / (a + b));
        }
    }
    cout << ans << "\n";
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
a, b <= 1e6
枚举 a 和 b
有 a + b < x 和 ab + a + b <= n
对 c 化简发现有 c <= x - (a + b) 且 c <= (n - ab) / (a + b), 取 min 即可
*/