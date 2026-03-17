#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int N = 2e5 + 10;
char s[N];

void check(int i, char op, int len, int& cnt)
{
    if(s[i] == op) return;
    if(i + 3 <= len && s[i] == '1' && s[i + 1] == '1' && s[i + 2] == '0' && s[i + 3] == '0') cnt--;
    if(i - 1 >= 1 && i + 2 <= len && s[i - 1] == '1' && s[i] == '1' && s[i + 1] == '0' && s[i + 2] == '0') cnt--;
    if(i - 2 >= 1 && i + 1 <= len && s[i - 2] == '1' && s[i - 1] == '1' && s[i] == '0' && s[i + 1] == '0') cnt--;
    if(i - 3 >= 1 && i <= len && s[i - 3] == '1' && s[i - 2] == '1' && s[i - 1] == '0' && s[i] == '0') cnt--;
    s[i] = op;
    if(i + 3 <= len && s[i] == '1' && s[i + 1] == '1' && s[i + 2] == '0' && s[i + 3] == '0') cnt++;
    if(i - 1 >= 1 && i + 2 <= len && s[i - 1] == '1' && s[i] == '1' && s[i + 1] == '0' && s[i + 2] == '0') cnt++;
    if(i - 2 >= 1 && i + 1 <= len && s[i - 2] == '1' && s[i - 1] == '1' && s[i] == '0' && s[i + 1] == '0') cnt++;
    if(i - 3 >= 1 && i <= len && s[i - 3] == '1' && s[i - 2] == '1' && s[i - 1] == '0' && s[i] == '0') cnt++;
}

void solve()
{
    string t;
    cin >> t;
    for(int i = 0; i < t.size(); i++) s[i + 1] = t[i];

    int cnt = 0, len = t.size();
    for(int i = 1; i + 3 <= len; i++)
        if(s[i] == '1' && s[i + 1] == '1' && s[i + 2] == '0' && s[i + 3] == '0') cnt++;
    
    int q; cin >> q;
    while(q--)
    {   
        char op;
        int pos;
        cin >> pos >> op;
        check(pos, op, len, cnt);
        if(cnt > 0) cout << "YES\n";
        else cout << "NO\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t = 1;
    cin >> t;
    while(t--) solve();
    return 0;
}