#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    vector<i64> pre(n + 1, 0);
    vector<i64> Sum(n + 1, 0);
    i64 sum = a[1];
    Sum[1] = a[1];
    for(int i = 2; i <= n; i++)
    {
        if(sum >= a[i]) pre[i] = pre[i - 1];
        else pre[i] = pre[i - 1] + (a[i] - sum);
        sum += a[i];
        Sum[i] = Sum[i - 1] + a[i];
    }
    
    while(q--)
    {
        int l, r; cin >> l >> r;
        cout << pre[r] + Sum[l - 1] - a[l] << "\n";
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
