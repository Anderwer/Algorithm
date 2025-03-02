#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<vector<i64>> a(n + 1, vector<i64>(n + 1));
    for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) cin >> a[i][j];

    vector<vector<i64>> pre1(n + 2, vector<i64>(n + 2, 0));
    vector<vector<i64>> pre2(n + 2, vector<i64>(n + 2, 0));
    vector<vector<i64>> pre3(n + 2, vector<i64>(n + 2, 0));

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            pre1[i][j] = pre1[i - 1][j] + pre1[i][j - 1] - pre1[i - 1][j - 1] + a[i][j] * i;
            pre2[i][j] = pre2[i - 1][j] + pre2[i][j - 1] - pre2[i - 1][j - 1] + a[i][j] * j;
            pre3[i][j] = pre3[i - 1][j] + pre3[i][j - 1] - pre3[i - 1][j - 1] + a[i][j];
        }
    }

    while(q--)
    {
        i64 xa, ya, xb, yb;
        cin >> xa >> ya >> xb >> yb;
        i64 k = yb - ya + 1;
        i64 c = -ya + 1 - k * xa;
        i64 sum1 = pre1[xb][yb] - pre1[xb][ya - 1] - pre1[xa - 1][yb] + pre1[xa - 1][ya - 1];
        i64 sum2 = pre2[xb][yb] - pre2[xb][ya - 1] - pre2[xa - 1][yb] + pre2[xa - 1][ya - 1];
        i64 sum3 = pre3[xb][yb] - pre3[xb][ya - 1] - pre3[xa - 1][yb] + pre3[xa - 1][ya - 1];
        cout << k * sum1 + sum2 + c * sum3 << " ";
    }
    cout << "\n";
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
如果从 [x1, y1] 到 [x2, y2]
假设 a[i][j] 在这个范围内, 那么有
ans += a[i][j] * ((i - x1) * (y2 - y1 + 1) + j - y1 + 1)
    += ki + j + c
其中, k = y2 - y1 + 1, c = -y1 + 1 - (y2 - y1 + 1) * x1
则 ans = ΣΣ k * A(i, j) * i + A(i, j) * j + c * A(i, j)

只需要提前算出 A(i, j) * i, A(i, j) * j 和 A(i, j) 的前缀和就可以 O(1) 给出query
*/