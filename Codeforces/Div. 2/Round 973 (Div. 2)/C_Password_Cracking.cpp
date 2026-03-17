#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

bool query(string s)
{
    int res;
    cout << "? " << s << endl;
    cin >> res;
    if(res) return true;
    else return false;
}

void solve()
{
    int n;
    cin >> n;
    string ans;
    while(ans.size() < n)
    {
        if(query(ans + "0")) ans += '0';
        else if(query(ans + "1")) ans += '1';
        else break;
    }
    while(ans.size() < n)
    {
        if(query("0" + ans)) ans = "0" + ans;
        else ans = "1" + ans;
    }
    cout << "! " << ans << endl;
}
int main()
{
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
