#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n, m, l;
    cin >> n >> m >> l;
    vector<array<int, 2>> hurdles(n + 1);
    vector<int> position(m + 1, 0);
    vector<int> power(m + 1, 0);
    for(int i = 1; i <= n; i++) cin >> hurdles[i][0] >> hurdles[i][1];
    for(int i = 1; i <= m; i++) cin >> position[i] >> power[i];

    int ans = 0, cur = 1;
    priority_queue<int> pq;
    for(int i = 1; i <= n; i++)
    {
        int L = hurdles[i - 1][1], R = hurdles[i][0];
        if(i == 1) L = 1;
        int need = hurdles[i][1] - hurdles[i][0] + 2;
        int pos = lower_bound(position.begin() + 1, position.end(), R) - position.begin();
        while(pos > m) pos--;
        while(pos >= 1 && position[pos] > R) pos--;
        if(i == 1)
        {
            for(int j = 1; j <= pos; j++) pq.push(power[j]);
        }
        else
        {
            while(pos >= 1 && position[pos] >= L)
            {
                pq.push(power[pos]);
                pos--;
            }
        }
        while(!pq.empty() && cur < need)
        {
            cur += pq.top();
            pq.pop();
            ans++;
        }
        if(cur < need)
        {
            cout << -1 << "\n";
            return;
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