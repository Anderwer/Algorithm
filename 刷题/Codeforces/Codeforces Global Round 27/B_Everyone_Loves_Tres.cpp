#include <bits/stdc++.h>
using namespace std;
using i64 = long long;


void solve()
{
    int n;
    cin >> n;
    if(~n & 1)
    {
        for(int i = 1; i <= n - 2; i++) cout << '3';
        cout << "66\n";
    }
    else
    {
        if(n < 5)
        {
            cout << -1 << "\n";
            return;
        }
        for(int i = 1; i <= n - 4; i++) cout << '3';
        cout << "6366\n";
    }
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