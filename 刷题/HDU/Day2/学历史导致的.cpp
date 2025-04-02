#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

string tian[10] = {"jia", "yi", "bing", "ding", "wu", "ji", "geng", "xin", "ren", "gui"};
string di[12] = {"zi", "chou", "yin", "mao", "chen", "si", "wu", "wei", "shen", "you", "xu", "hai"};
unordered_map<string, int> mp;

void solve()
{
    string s;
    cin >> s;
    cout << mp[s] << "\n";
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    cin >> t;
    int cur = 1984;
    int a = 0, b = 0;
    while(cur <= 2043)
    {
        mp[tian[a] + di[b]] = cur;
        cur++;
        a = (a + 1) % 10;
        b = (b + 1) % 12;
    }
    while(t--){
        solve();
    }
    return 0;
}
