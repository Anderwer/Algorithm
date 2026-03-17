#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n, k;
    cin >> n >> k;
    map<int, int> cnt;
    for(int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        cnt[x]++;
    }
    deque<int> q;
    int ans = 0, now = 0;
    for(auto [x,y] : cnt)
    {
        if(q.empty())
        {
            q.push_back(x);
            now += y;
            ans = max(ans, now);
            continue;
        }
        if(q.back() == x - 1)
        {
            if(q.size() < k)
            {
                q.push_back(x);
                now += y;
            }
            else
            {
                now -= cnt[q.front()];
                q.pop_front();
                q.push_back(x);
                now += y;
            }
        }
        else
        {
            while(!q.empty() && q.back() != x - 1)
            {
                now -= cnt[q.back()];
                q.pop_back();
            }
            q.push_back(x);
            now += y;
        }
        ans = max(ans, now);
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
