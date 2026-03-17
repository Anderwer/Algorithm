#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n, d;
    cin >> n >> d;
    cout << 1 << " ";
    if(n >= 3 || d % 3 == 0) cout << 3 << " ";
    if(d == 5) cout << 5 << " ";
    if(n >= 3 || d % 7 == 0) cout << 7 << " ";
    for(int i = 1; i <= n; i++)
    {
        if((i * d) % 9 == 0 || n >= 6)
        {
            cout << 9 << " ";
            break;
        }
    }
    cout << "\n";
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
一个自然数从个位向左，逐位依次用1、3、2、－1、－3、－2分别乘各个数位上的数再相加，如果得数能被7整除(0也算），这个自然数就能被7整除。

能被9整除的数，各个数位上的数字和能被9整除，那么这个数能被9整除
*/