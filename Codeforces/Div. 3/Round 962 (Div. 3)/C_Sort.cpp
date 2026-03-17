#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n, q;
    cin >> n >> q;
    string a, b;
    cin >> a >> b;
    
    vector<vector<int>> cnt_a(30, vector<int>(n + 10, 0));
    vector<vector<int>> cnt_b(30, vector<int>(n + 10, 0));
    for(int i = 1; i <= 26; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(j > 0) cnt_a[i][j] = cnt_a[i][j - 1];
            if(j > 0) cnt_b[i][j] = cnt_b[i][j - 1];
            if(a[j] - 'a' + 1 == i) cnt_a[i][j] ++;
            if(b[j] - 'a' + 1 == i) cnt_b[i][j] ++;
        }
    }

    while(q--)
    {
        int l, r; cin >> l >> r;
        l--, r--;
        int res = 0;
        for(int i = 1; i <= 26; i++)
        {
            if(l == 0) res += abs(cnt_a[i][r] - cnt_b[i][r]);
            else res += abs(cnt_a[i][r] - cnt_a[i][l - 1] - cnt_b[i][r] + cnt_b[i][l - 1]);
        }
        cout << res / 2 << '\n';
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
