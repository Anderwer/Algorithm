#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int a[2], b[2];
    cin >> a[0] >> a[1] >> b[0] >> b[1];
    int ans = 0;
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++) 
            if((a[i] > b[j] && a[1 - i] > b[1 - j]) || (a[i] == b[j] && a[1 - i] > b[1 - j]) || (a[i] > b[j] && a[1 - i] == b[1 - j])) ans++;

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
