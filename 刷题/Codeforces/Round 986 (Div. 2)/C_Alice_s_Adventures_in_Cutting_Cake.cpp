#include <bits/stdc++.h>
using i64 = long long;
using namespace std;


void solve()
{
    int n, m, v;
    cin >> n >> m >> v;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    vector<i64> pre(n + 1, 0);
    for(int i = 1; i <= n; i++) pre[i] = pre[i - 1] + a[i];

    vector<int> fL(n + 1, 0), fR(n + 2, 0);
    vector<int> fr(n + 1, 0);
    i64 cur = 0;
    for(int i = 1; i <= n; i++)
    {
        if(cur + a[i] < v)
        {
            fL[i] = fL[i - 1];
            cur += a[i];
        }
        else
        {
            fL[i] = fL[i - 1] + 1;
            cur = 0;
        }
    }
    cur = 0;
    for(int i = n; i >= 1; i--)
    {
        if(cur + a[i] < v)
        {
            fR[i] = fR[i + 1];
            cur += a[i];
        }
        else
        {
            fR[i] = fR[i + 1] + 1;
            cur = 0;
        }
    }

    if(fL[n] < m)
    {
        cout << -1 << "\n";
        return;
    }
    i64 ans = 0;
    for(int i = 1; i <= n; i++) //1#.
    {
        if(fL[i] == m)
        {
            ans = max(ans, pre[n] - pre[i]);
            break;
        }
    }
    for(int i = n; i >= 1; i--) //2#.
    {
        if(fR[i] == m)
        {
            ans = max(ans, pre[i - 1]);
        }
    }
    
    for(int i = 1; i <= n; i++) fr[i] = fR[n - i + 1]; //3#.
    for(int i = 1; i <= n; i++)
    {
        int pos = lower_bound(fr.begin() + 1, fr.end(), m - fL[i - 1]) - fr.begin();
        ans = max(ans, pre[n - pos] - pre[i - 1]);
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
Alice 的那一份有三种情况
一种是头部, 一种是尾部, 还有一种是中间部分
我们可以维护一个 fL[i] : 从 1 到 i 最多可以分成 >= v 的份数
再维护一个 fR[i] : 从 n 到 i 最多可以分成 >= v 的份数

1#. Alice 分尾部时, 我们找到第一个 fL[i] == m 的下标, 然后 [i + 1, n] 都是 Alice 的

2#. Alice 分头部时, 我们找到第一个 fR[i] == m 的下标, 然后 [1, i - 1] 都是 Alice 的

3#. Alice 分中间时, 我们设 fL[i] == x, fR[j] == y, 当 x + y == m 时, [x + 1, y - 1] 都是 Alice 的

这些情况取最大值即可
*/