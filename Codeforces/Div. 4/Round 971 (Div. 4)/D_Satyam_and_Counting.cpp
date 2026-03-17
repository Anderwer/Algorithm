#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

const int N = 2e5 + 10;
bool p[N][2];

void solve()
{
    int n;
    cin >> n;
    for(int i = 0; i <= n; i++) p[i][0] = p[i][1] = false;
    for(int i = 1; i <= n; i++)
    {
        int x, y;
        cin >> x >> y;
        p[x][y] = true;
    }
    i64 ans = 0;
    for(int i = 0; i <= n; i++)
    {
        if(p[i][0] && p[i][1]) ans += n - 2;
        if(i > 0 && p[i][0] && p[i - 1][1] && p[i + 1][1]) ans++;
        if(i > 0 && p[i][1] && p[i - 1][0] && p[i + 1][0]) ans++;
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
确定一个点(x, 0)
如果(x, 1)有一个点,则(x,0)右边有多少个点就有多少个直角三角形
如果(x + 1, 1)有一个点, 且(x + 2, 0)有一个点, 则构成一个

确定一个点(x, 1)
如果(x, 0)有一个点, 则(x, 1)右边有多少个点就有多少个三角形
如果(x + 1, 0)有一个点, 且(x + 2, 1)有一个点, 则构成一个

*/