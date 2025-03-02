#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void dfs(int l, int r, int n, int k, i64& ans)
{
    if(r - l + 1 < k) return; 
    int m = (l + r) / 2;
    if((r - l + 1) % 2 == 0)
    {
        dfs(l, m, n, k, ans);
        dfs(m + 1, r, n, k, ans);
    }
    else
    {
        ans += m;
        if(l == r) return;
        dfs(l, m - 1, n, k, ans);
        dfs(m + 1, r, n, k, ans);
    }
}

void solve()
{
    i64 n, k;
    cin >> n >> k;
    i64 ans = 0, cur = 1, x = n + 1;
    while(n >= k)
    {
        if(n & 1) ans += cur;
        n >>= 1;
        cur <<= 1;
    }
    cout << x * ans / 2 << "\n";
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
