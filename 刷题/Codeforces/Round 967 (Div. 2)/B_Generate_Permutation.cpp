#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    if(~n & 1) cout << -1 << "\n";
    else 
    {
        for(int i = (n + 1) / 2; i >= 1; i--) cout << i << " ";
        for(int i = (n + 1) / 2 + 1; i <= n; i++) cout << i << " ";
        cout << "\n";
    }    
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
