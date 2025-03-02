#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    string s;
    cin >> s;
    i64 sum = 0;
    int cnt_2 = 0, cnt_3 = 0;
    for(auto v : s)
    {
        sum += (v - '0');
        if(v == '2') cnt_2++;
        if(v == '3') cnt_3++;
    }
    //cout << cnt_2 << " " << cnt_3 << "\n";
    if(sum % 9 == 0)
    {
        cout << "YES\n";
        return;
    }
    int x = 9 - (sum % 9);
    for(int i = 0; i <= cnt_2; i++)
    {
        for(int j = 0; j <= cnt_3; j++)
        {
            if((2 * i + 6 * j) % 9 == x)
            {
                cout << "YES\n";
                return;
            }
        }
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
