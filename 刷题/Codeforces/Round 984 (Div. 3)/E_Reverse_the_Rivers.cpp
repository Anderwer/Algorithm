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
        int m; cin >> m;
        int L = 0, R = n - 1;
        while(m--)
        {
            char o;
            int r, c;
            cin >> r >> o >> c;
            if(o == '<')
            {
                int left = 0, right = n - 1;
                while(left <= right)
                {
                    int mid = (left + right) / 2;
                    if(regions[r][mid] >= c) right = mid - 1;
                    else left = mid + 1;
                }
                R = min(R, right);
            }
            else
            {
                int left = 0, right = n - 1;
                while(left <= right)
                {
                    int mid = (left + right) / 2;
                    if(regions[r][mid] > c) right = mid - 1;
                    else left = mid + 1;
                }
                L = max(L, left);
            }
        }
        if(L <= R) cout << L + 1 << "\n";
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