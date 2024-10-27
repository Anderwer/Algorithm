#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 2010;

int a[N];

void solve()
{
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    int ans = 1e9;
    for(int i = 1; i <= n; i++)
    {
        int cnt = i - 1;
        for(int j = i + 1; j <= n; j++) if(a[j] > a[i]) cnt++;
        ans = min(ans, cnt);
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
对于一个位置, 前面的都要去掉, 统计一下后面有多少个数比它大, 最小值为ans
*/
