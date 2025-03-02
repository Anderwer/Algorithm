#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n, a, b;
    cin >> n >> a >> b;
    string s;
    cin >> s;
    int cnt = 0, x = 0, y = 0;
    while(cnt <= 200)
    {
        for(int i = 0; i < n; i++)
        {
            if(s[i] == 'N') y++;
            if(s[i] == 'E') x++;
            if(s[i] == 'S') y--;
            if(s[i] == 'W') x--;
            if(x == a && y == b)
            {
                cout << "YES\n";
                return;
            }
        }
        cnt += n;
    }
    cout << "NO\n";
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
