#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> a(n + 1), b(m + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int j = 1; j <= m; j++) cin >> b[j];

    i64 sum_a = 0, sum_b = 0;
    for(int i = 1; i <= n; i++) sum_a += a[i];
    for(int i = 1; i <= m; i++) sum_b += b[i];
    
    unordered_map<i64, bool> vis1, vis2, ans;
    for(int i = 1; i <= n; i++) vis1[sum_a - a[i]] = true;
    for(int i = 1; i <= m; i++) vis2[sum_b - b[i]] = true;
    for(int i = 1; i <= 2e5; i++)
    {

        for(int j = 1; j * i <= 2e5; j++)
        {
            ans[i * j] |= vis1[i] && vis2[j];
            ans[i * j] |= vis1[-i] && vis2[-j];
            ans[-i * j] |= vis1[-i] && vis2[j];
            ans[-i * j] |= vis1[i] && vis2[-j];
        }
    }
    while(q--)
    {
        int x; cin >> x;
        if(ans[x] == true) cout << "YES\n";
        else cout << "NO\n";
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
    return 0;
}

/*
数学推理, 对于一个 r, c 有:
X = sum - a[r] * sum_b - b[c] * sum_a + a[r] * b[c]
  = sum_a * sum_b - a[r] * sum_b - b[c] * sum_a + a[r] * b[c]
  = (sum_a - a[r]) * (sum_b - b[c])

由于查询的 x 范围是 |x| <= 2e5
设 L = sum_a - a[r], R = sum_b - b[c]
我们将所有不同的 L 和 R 分别在两个 vis 数组中
然后通过从 -2e5 ~ 2e5 枚举 L 和 R 并标记在 ans[] 中即可 
*/