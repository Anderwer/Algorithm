#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n, k, p, m;
    cin >> n >> k >> p >> m;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    int w = a[p];

    vector<int> pre;
    for(int i = 1; i < p; i++) pre.push_back(a[i]);
    sort(pre.begin(), pre.end());

    int first = w;
    for(int i = 0; i < max(0, p - k); i++) first += pre[i];

    if(first > m)
    {
        cout << 0 << "\n";
        return;
    }

    vector<int> other;
    for(int i = 1; i <= n; i++)
    {
        if(i == p) continue;
        other.push_back(a[i]);
    }
    sort(other.begin(), other.end());

    int cycle = w;
    for(int i = 0; i < n - k; i++) cycle += other[i];

    cout << 1 + (m - first) / cycle << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--)
    {
        solve();
    }
    return 0;
}
