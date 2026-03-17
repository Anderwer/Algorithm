#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    string s;
    cin >> s;
    int ans = 0;
    for(int i = 0; i < n; i++)
    {
        int cnt = 0;
        for(int j = i; j < n; j++)
        {
            if(s[j] == '0') cnt++;
            if(cnt == m)
            {
                i = j + k - 1;
                ans++;
                break;
            }
            if(s[j] == '1')
            {
                i = j;
                break;
            }
        }
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
