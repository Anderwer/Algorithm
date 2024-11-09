#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 2e5 + 10;
string a[N];

void solve()
{
    int n, q;
    cin >> n >> q;
    map<string, vector<int>> mp;
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i];
        mp[a[i]].push_back(i);
    }

    while(q--)
    {
        int x, y; cin >> x >> y;
        int res = 1e9;
        if(a[x][0] == a[y][0] || a[x][0] == a[y][1] || a[x][1] == a[y][0] || a[x][1] == a[y][1]) res = abs(x - y);
        else
        {
            string A = a[x], B = a[y];
            for(int i = 0; i <= 1; i++)
            {
                for(int j = 0; j <= 1; j++)
                {
                    string now;
                    now += A[i]; now += B[j];
                    if(now[0] > now[1]) swap(now[0], now[1]);
                    auto it = lower_bound(mp[now].begin(), mp[now].end(), x);
                    if(it != mp[now].end()) res = min(res, abs(x - *it) + abs(y - *it));
                    if(it != mp[now].begin()) res = min(res, abs(x - *prev(it)) + abs(y - *prev(it)));
                }
            }
        }
        if(res == 1e9) cout << -1 << "\n";
        else cout << res << "\n";
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

/*
给定两个城市 x 和 y
一共有两种情况:
    x 和 y 有相同的颜色, 则答案就是 |x - y|
    x 和 y 没有相同的颜色, 然而一共就四种颜色, 假设 x 颜色是 BG, 那 y 的就是 RY, 我们只需要找一个带有 'BR', 'BY', 'GR', 'GY' 的城市作为中转站即可

对于第二种情况, 我们假设中转城市是 Z
如果 Z 在 x 和 y 中间, 则 ans = |x - y|
如果 Z 在 x 和 y 之外, 则 ans = |x + y - 2 * Z|

*/