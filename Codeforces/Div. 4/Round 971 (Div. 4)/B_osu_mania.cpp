#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

const int N = 505;
char mp[N][5];
void solve()
{
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= 4; j++) cin >> mp[i][j];

    for(int i = n; i >= 1; i--)
        for(int j = 1; j <= 4; j++) if(mp[i][j] == '#') cout << j << " ";

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
