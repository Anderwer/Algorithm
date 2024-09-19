#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

const int N = 1005;
string s[N];
string v = "narek"; //01234
int f[5]; //设以"narek"中第i个字母结尾的最大总得分
int f_tmp[5]; //临时存储dp

void solve()
{
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> s[i];
    for(int i = 0; i < 5; i++) //init
    {
        if(i == 0) f[i] = 0;
        else f[i] = -1e9;
    }
    for(int i = 1; i <= n; i++) // search each string
    {
        for(int x = 0; x < 5; x++) f_tmp[x] = f[x];
        for(int j = 0; j < 5; j++) //search what letter dp
        {
            if(f[j] == -1e9) continue; //if dp = -1e9, it hasn't been searched
            int pos = j, cnt = 0;
            for(int k = 0; k < m; k++) //search this string's each letter
            {
                int index = v.find(s[i][k]);
                if(index == -1) continue; // no "narek"
                if(pos == index) 
                {
                    pos = (pos + 1) % 5;
                    cnt++;
                }
                else cnt--;
            }
            f_tmp[pos] = max(f_tmp[pos], f[j] + cnt);
        }
        for(int x = 0; x < 5; x++) f[x] = f_tmp[x];
    }
    int ans = 0;
    for(int i = 0; i < 5; i++) ans = max(ans, f[i] - 2 * i);
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
ans = score_n - score_c = score_n - (len - 非"narek"的数量) 
    = score_n - len + 非"narek"的数量

*/