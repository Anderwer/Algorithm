#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

string s = "aeiou";
void solve()
{
    int n;
    cin >> n;
    string ans;
    int cnt[5] = {0};
    for(int i = 0; i < n; i++) cnt[i % 5]++;
    for(int i = 0; i < 5; i++)
    {
        for(int j = 1; j <= cnt[i]; j++) ans += s[i];
    }
    cout << ans << "\n";
    
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
a 1
ae 2
aei 3
aeio 4
aeiou 5
aaeiou 7
aaeeiou 9
aaeeiiou 11
aaeeiioou 13
aaeeiioouu 15
*/