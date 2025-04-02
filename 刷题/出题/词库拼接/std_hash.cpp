#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<string> s(n + 1);
    for(int i = 1; i <= n; i++) cin >> s[i];

    unordered_map<string, bool> Hash; // 哈希表存字符串
    for(int i = 1; i <= n; i++)
        Hash[s[i]] = true;

    int ans = 0;
    for(int i = 1; i <= n; i++)
    {
        int len = s[i].size();
        for(int j = 1; j < len; j++)
        {
            string pre = s[i].substr(0, j);
            string suf = s[i].substr(j);
            if(Hash.count(pre) && Hash.count(suf)) ans++;
        }
    }
    cout << ans << "\n";
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    solve();
    return 0;
}
