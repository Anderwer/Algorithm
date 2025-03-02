#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(m + 1), q(n + 1);
    for(int i = 1; i <= m; i++) cin >> a[i]; //不包含 a[i] 的问题集
    for(int i = 1; i <= k; i++)
    {
        int x; cin >> x;
        q[x] = 1;
    }

    if(k < n - 1) //不存在
    {
        for(int i = 1; i <= m; i++) cout << 0;
        cout << "\n";
    }
    else if(k == n)
    {
        for(int i = 1; i <= m; i++) cout << 1;
        cout << "\n";
    }
    else //k == n - 1
    {
        int cannot;
        for(int i = 1; i <= n; i++)
        {
            if(q[i] == 0) cannot = i;
        }
        for(int i = 1; i <= m; i++)
        {
            if(a[i] == cannot) cout << 1;
            else cout << 0;
        }
        cout << "\n";
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
