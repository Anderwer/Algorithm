#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 2e5 + 10;
int a[N];

void solve()
{
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    
    int m; cin >> m;
    while(m--)
    {
        string s; cin >> s;
        if(s.size() != n) cout << "NO\n";
        else
        {
            bool flag = true;
            map<char, int> mp;
            map<int, char> vis;
            for(int i = 0; i < n; i++)
            {
                if(mp.count(s[i]) == 0) //字符没有对应数字
                {
                    if(vis.count(a[i + 1]) == 0) //字符没有对应数字且数字没有对应字符
                    {
                        mp[s[i]] = a[i + 1];
                        vis[a[i + 1]] = s[i];
                    }
                    else //字符没有对应数字且数字对应了字符
                    {
                        if(vis[a[i + 1]] != s[i]) flag = false;
                    }
                }
                else //字符对应了数字
                {
                    if(mp[s[i]] != a[i + 1]) flag = false;
                }
                if(flag == false) break;
            }
            if(flag) cout << "YES\n";
            else cout << "NO\n";
        }
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
