#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

void solve()
{
    int n;
    cin >> n;
    int cnt_1 = 0, cnt_0 = 0;
    for(int i = 1; i <= n * 2; i++)
    {
        int x; cin >> x;
        if(x) cnt_1 ++;
        else cnt_0 ++;
    }
    int ans_min = (cnt_1 & 1);
    int ans_max = min(cnt_0, cnt_1);
    cout << ans_min << " " << ans_max << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t = 1;
    cin >> t;
    while(t--) solve();
    return 0;
}

/*
0 0 暗
0 1 亮
1 1 暗
*/