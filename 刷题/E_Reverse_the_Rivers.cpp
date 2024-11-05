#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

void solve()
{
    int n, k, q;
    cin >> n >> k >> q;
    vector<vector<int>> a(n + 1, vector<int>(k + 1));
    vector<vector<int>> b(n + 1, vector<int>(k + 1));
    vector<int> regions[k + 1];
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= k; j++) cin >> a[i][j];

    for(int i = 1; i <= k; i++)
        for(int j = 1; j <= n; j++) b[j][i] = b[j - 1][i] | a[j][i];
    
    for(int i = 1; i <= k; i++) //枚举地区
        for(int j = 1; j <= n; j++) regions[i].push_back(b[j][i]);

    while(q--) // qlogn
    {   
        bool flag = true;
        int m, x; cin >> m, x = m;
        int L = 1, R = 1e9;
        while(x--)
        {
            char o;
            int r, c;
            cin >> r >> o >> c;
            int pos = upper_bound(regions[r].begin(), regions[r].end(), c) - regions[r].begin();
            if(o == '>') // 为 > 时, 区间[pos + 1, n]都满足
            {
                //printf("[%d, %d]\n", pos + 1, n);
                L = max(L, pos + 1);
            }
            else        // 为 < 时, 区间[1, pos]都满足
            {
                //printf("[%d, %d]\n", 1, pos);
                R = min(R, pos);
            }
        }
        if(L <= R) cout << L << "\n";
        else cout << -1 << "\n";
    }

}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t = 1;
    //cin >> t;
    while(t--) solve();
    return 0;
}