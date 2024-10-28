#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    if(n == 1)
    {
        cout << 0 << "\n";
        return;
    }
    int cnt = n - 1;
    for(int i = 1; i <= cnt; i++) cout << 0;
    cout << 1 << "\n";
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
f(t) : 不包含 '1' 的字串个数
g(t) : 至少包含一个 '1' 的字串个数

则 g(t) = 子串总数 - f(t)
|f(t) - g(t) | = |子串总数 - f(t) * 2|
子串总数 = Σ C[n][i] = 2^n - 1
含有 x 个 '0' 的 f(t) = Σ C[x][i] = 2^x - 1

则 |f(t) - g(t)| = |2^n - 2^(x + 1) + 1|, 只要令 x + 1 = n 即可求出 字符串中有多少个 '0'
*/