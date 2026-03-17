#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    string s, r;
    cin >> n >> s >> r;

    int cnt_0 = 0, cnt_1 = 0;
    for(auto v : s)
    {
        if(v == '0') cnt_0 ++;
        else cnt_1 ++;
    }

    for(auto v : r)
    {
        if(cnt_0 == 0 || cnt_1 == 0)
        {
            cout << "NO\n";
            return;
        }
        if(v == '0') cnt_1 --;
        else cnt_0 --;
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
选择一个 k 且 s[k] != s[k + 1] 时, 如果 r[k] == s[k], 则 s[k] 不变

如果当前 r[i] == '1', 则 s 中的 "10" 或 "01" 会变成 '1'
如果当前 r[i] == '0', 则 s 中的 "10" 或 "01" 会变成 '0'
则问题转化为, 当 r = 1 时 s 减少一个 0, 当 r = 0 时 s 减少一个 1
*/