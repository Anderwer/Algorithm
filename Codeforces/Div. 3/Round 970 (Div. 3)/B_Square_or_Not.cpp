#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    string s;
    cin >> n >> s;
    bool ans = false;
    int cnt = 0;
    for(int i = 0; i < n; i++) if(s[i] == '1') cnt++;
    int x = sqrt(n);
    if(x * x == n)
    {
        if(n == 4 && cnt == 4) ans = true;
        else if(4 * x - 4 == cnt) ans = true;
    }
    if(ans) cout << "Yes\n";
    else cout << "No\n";
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
一个 r 行 c 列的矩阵
外围的1的个数 : 2 * (r + c) - 4

*/