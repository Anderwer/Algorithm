#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<array<int, 3>> range(n + 1);
    for(int i = 1; i <= n; i++)
    {
        cin >> range[i][0] >> range[i][1];
        range[i][2] = i;
    }

    sort(range.begin() + 1, range.end());
    vector<int> ans(n + 1, 0);
    priority_queue<array<int, 2>, vector<array<int, 2>>, greater<array<int, 2>>> pq;
    int pos = 1;
    for(int i = 1; i <= n; i++)
    {
        while(pos <= n && range[pos][0] <= i)
        {
            pq.push({range[pos][1], range[pos][2]});
            pos++;
        }
        if(pq.empty() || pq.top()[0] < i)
        {
            cout << -1 << "\n";
            return;
        }
        auto cur = pq.top();
        pq.pop();
        ans[cur[1]] = i;
    }
    for(int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << "\n";
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
