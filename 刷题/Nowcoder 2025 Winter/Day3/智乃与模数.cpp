#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++)
    {
        a[i] = n % i;
    }
    sort(a.begin() + 1, a.end(), greater<int>());
    for(int k = 1; k <= n; k++)
    {
        int sum = 0;
        for(int i = 1; i <= k; i++) sum += a[i];
        cout << sum << ",";
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
