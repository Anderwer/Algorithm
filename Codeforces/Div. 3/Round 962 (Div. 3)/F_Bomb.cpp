#include <bits/stdc++.h>
#define int long long
using i64 = long long;
using namespace std;
int n, k;

bool check(int val, vector<int>& a, vector<int>& b)
{
    int num = 0;
    for(int i = 1; i <= n; i++)
    {
        if(a[i] < val) continue;
        num += (a[i] - val) / b[i] + 1;
    }
    return num >= k;
}

void solve()
{
    cin >> n >> k;
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) cin >> b[i];

    int l = 0, r = 1e9 + 10, res = 0;
    while(l <= r)
    {
        int mid = (l + r) / 2;
        if(check(mid, a, b))
        {
            res = mid;
            l = mid + 1;
        }
        else r = mid - 1;
    }

    i64 ans = 0, cur = 0;
    for(int i = 1; i <= n; i++)
    {
        if(a[i] < res) continue;
        i64 times = (a[i] - res) / b[i] + 1;
        ans += times * a[i] - times * (times - 1) * b[i] / 2; //等差求和
        cur += times;
    }
    ans -= (cur - k) * res; //多的
    cout << ans << '\n';
}

signed main()
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
对于一个 a[i], 如果它被选过 x 次, 那么最终它变为 val = a[i] - x * b[i]
假设我们最后一次选完给答案的贡献是 val, 那么之前选的给答案带来的贡献 >= val
我们给定一个 val, 然后遍历 a[] 算出每个 a[i] 变为 < val 要多少次, 再判断次数 <= k 即可
对于val 的选取, 明显具有单调性, 因为 val 越高, 次数越少

*/