#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<char> s(n + 1);
    for(int i = 1; i <= n; i++) cin >> s[i];

    for(int i = 1; i <= n; i++)
    {
        if(s[i] == 'p')
        {
            for(int j = i + 1; j <= n; j++)
            {
                if(s[j] == 's')
                {
                    cout << "NO\n";
                    return;
                }
            }
        }
        if(s[i] == 's' && i != 1)
        {
            for(int j = i + 1; j <= n; j++)
            {
                if(s[j] == 'p' && j != n)
                {
                    cout << "NO\n";
                    return;
                }
            }
        }
    }
    cout << "YES\n";
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

/*
如果 s[i] == 's', 那么 [i, n] 中包含了 1 ~ n - i + 1
如果 s[i] == 'p', 那么 [1, i] 中包含了 1 ~ i
*/