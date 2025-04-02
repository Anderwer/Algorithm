#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
i64 n, k;

bool check(i64 x, vector<i64>& a)
{
    i64 cnt = 0;
    for(int L = 1; L <= n; L++)
    {
        int l = L, r = n, R = L;
        while(l <= r)
        {
            int mid = (l + r) / 2;
            if(a[L] * a[mid] < x) l = mid + 1, R = mid;
            else r = mid - 1;
        }
        cnt += R - L;
    }
    return cnt <= k - 1;
}

void solve()
{   
    cin >> n >> k;
    vector<i64> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    sort(a.begin() + 1, a.end());

    i64 l = 1, r = 1e18, ans = 0;
    while(l <= r)
    {
        i64 mid = (l + r) / 2;
        if(check(mid, a)) l = mid + 1, ans = mid;
        else r = mid - 1;
    }
    cout << ans << "\n";
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    solve();
    return 0;
}
