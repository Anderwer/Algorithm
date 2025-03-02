#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    if(n <= 4) cout << -1 << "\n";
    else
    {
        for(int i = 2; i <= n; i += 2)
        {
            if(i != 4) cout << i << " ";
        }
        cout << "4 5 1 3 ";
        for(int i = 7; i <= n; i += 2) cout << i << " ";
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
