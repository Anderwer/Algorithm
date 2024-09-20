#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int a, b;
    cin >> a >> b;
    bool flag = false;
    if(a % 2 == 0 && b % 2 == 0) flag = true;
    else if(a % 2 == 0 && b % 2 == 1 && a >= 2) flag = true;
    if(flag) cout << "YES\n";
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
当a为偶数时可以看做a=0
当b为偶数时可以看做b=0
如果a,b都是偶数, YES
如果a是奇数, b是偶数.总有一个1无法消除, NO
如果a是偶数, b是奇数, 那么b会预留一个2, 此时a可以留2个抵消: 当a < 2 时 NO , 当 a >= 2 时YES
*/