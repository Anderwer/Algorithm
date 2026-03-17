#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    string s;
    cin >> s;
    
    int len = 1, pos = 0;
    for(int i = 0; i < s.size(); i++)
    {
        if(s[i] == '0')
        {
            len = s.size() - i;
            pos = i;
            //cout << len;
            break;
        }
    }

    if(pos == 0)
    {
        cout << "1 1 1 " << s.size() << "\n";
        return;
    }

    vector<int> res(len, 0);
    vector<int> tmp(len, 0);
    int ans = 0;
    for(int i = 0; i + len <= s.size(); i++)
    {
        for(int j = 0; j < len; j++)
        {
            if(s[i + j] == s[pos + j]) tmp[j] = 0;
            else tmp[j] = 1;
        }
        for(int j = 0; j < len; j++)
        {
            if(tmp[j] < res[j]) break;
            if(tmp[j] > res[j])
            {
                res = tmp;
                ans = i + 1;
                break;
            }
        }
    }
    cout << ans << " " << ans + len - 1 << " " << 1 << " " << s.size() << "\n";
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
