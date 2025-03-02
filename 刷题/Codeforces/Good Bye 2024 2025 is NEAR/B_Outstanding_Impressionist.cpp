#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<int> l(n + 1), r(n + 1);
    for(int i = 1; i <= n; i++) cin >> l[i] >> r[i];

    vector<int> cnt(n * 2 + 10, 0);
    vector<i64> mark(n * 2 + 10, 0);
    for(int i = 1; i <= n; i++)
    {
        if(l[i] == r[i]) cnt[l[i]]++, mark[l[i]] = 1;
    }
    for(int i = 1; i <= n * 2 + 5; i++) mark[i] += mark[i - 1];
    for(int i = 1; i <= n; i++)
    {
        if(l[i] == r[i])
        {
            if(cnt[l[i]] == 1) cout << 1;
            else cout << 0;
        }
        else
        {
            if(mark[r[i]] - mark[l[i] - 1] == r[i] - l[i] + 1) cout << 0;
            else cout << 1;
        }
    }
    cout << '\n';

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
