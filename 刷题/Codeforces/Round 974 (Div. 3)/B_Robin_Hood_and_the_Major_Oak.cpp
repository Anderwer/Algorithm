#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

void solve()
{
    int n, k;
    cin >> n >> k;
    int L = n - k + 1;
    int R = n;
    int odd = 0;
    if(L & 1 && R & 1) odd = (R - L + 1) / 2 + 1;
    else odd = (R - L + 1) / 2;
    if(odd & 1) cout << "NO\n";
    else cout << "YES\n";
}

int main() 
{
    int t = 1;
    cin >> t;
    while(t--) solve();
    return 0;
}
/*
给n , k
从第一年到第n年，有一棵树， 现在是第i年，那么这棵树会长i^i个叶子
i ~ i + k
到第n年时，树上的叶子数量是奇数还是偶数

[5, 10] : (R - L + 1) / 2
[5, 11] : (R - L + 1) / 2 + 1
[6, 10] : (R - L + 1) / 2
[6, 11] : (R - L + 1) / 2
*/