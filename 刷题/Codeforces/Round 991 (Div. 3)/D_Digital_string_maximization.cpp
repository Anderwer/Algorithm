#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    string s;
    cin >> s;
    int n = s.size();
    for(int i = 0; i < n; i++)
    {
        int pos = 0;
        int mx = s[i];
        for(int j = i + 1; j <= i + 9 && j < n; j++)
        {   
            if(s[j] - j + i > mx)
            {
                mx = s[j] - j + i;
                pos = j;
            }
        }
        for(int j = pos; j > i; j--) s[j] = s[j - 1];
        s[i] = mx;
        //cout << s << "\n";
    }
    cout << s << "\n";
     
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
