#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n, q;
    cin >> n >> q;
    map<string, int> mp;

    int sum = 0;
    for(int i = 1; i <= n; i++)
    {
        string s; cin >> s;
        if(mp[s] == 0) sum++;
        mp[s]++;
    }
    
    while(q--)
    {
        int op; cin >> op;
        if(op == 1)
        {
            int m; cin >> m;
            for(int i = 1; i <= m; i++)
            {
                string s; cin >> s;
                if(mp[s] == 0) sum++;
                mp[s]++;
            }
        }
        else if(op == 2)
        {
            int m; cin >> m;
            for(int i = 1; i <= m; i++)
            {
                string s; cin >> s;
                if(mp.count(s) == 0)
                {
                    cout << "NO\n";
                    cout << sum << "\n";
                }
                else
                {
                    cout << "YES\n";
                    cout << mp[s] << "\n";
                }
            }
        }
        else if(op == 3)
        {
            for(auto& [k, v] : mp) cout << k << " " << v << "\n";
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    solve();
    return 0;
}