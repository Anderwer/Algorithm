#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    vector<int> mark(n + 1, 0);
    vector<int> ans(n + 1, 0);
    for(int i = 1; i <= n; i++)
    {
        if(mark[a[i]] == 0)
        {
            ans[i] = a[i];
            mark[a[i]] = 1;
        }
    }
    int now = 1;
    for(int i = 1; i <= n; i++)
    {
        while(mark[now] == 1) now++;
        if(ans[i] == 0)
        {
            ans[i] = now;
            mark[now] = 1;
        }
    }
    for(int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << "\n";
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
