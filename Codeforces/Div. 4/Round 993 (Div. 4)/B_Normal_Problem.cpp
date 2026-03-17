#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    string s;
    cin >> s;
    for(int i = s.size() - 1; i >= 0; i--)
    {
        if(s[i] == 'w') cout << 'w';
        else if(s[i] == 'p') cout << 'q';
        else if(s[i] == 'q') cout << 'p';
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
