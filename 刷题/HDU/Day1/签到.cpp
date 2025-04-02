#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    string p;
    cin >> p;

    int ans = -1;
    for(int i = 1; i <= n; i++) 
    {
        string s;
        cin >> s;
        if(s == p) ans = i;
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
