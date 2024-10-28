#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 2e5 + 10;
char a[N];

void solve()
{
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    
    bool is_win = false;
    if(a[1] == '1' || a[n] == '1') is_win = true;
    for(int i = 1; i < n; i++)
    {
        if(a[i] == '1' && a[i + 1] == '1') is_win = true;
    }
    if(is_win) cout << "YES\n";
    else cout << "NO\n";

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
注意有个规则, 如果语句中存在 'and', 则优先处理 'and'语句

因此：
如果字符串第一个是 '1',  在它右侧放一个 'or', 则语句永远为 true
如果字符串最后一个是 '1',  在它左侧放一个 'or', 则语句永远为 true
如果字符串中存在至少两个连续的 '1', 则语句永远为 true, 因为不管左边的 '1' 的左边是什么, 都可以放一个 'or', 右边同理

*/