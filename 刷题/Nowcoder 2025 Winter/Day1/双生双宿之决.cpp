#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    if(n & 1)
    {
        cout << "No\n";
        return;
    }
    map<int, int> cnt;
    int num = 0;
    for(int i = 1;  i <= n; i++)
    {
        if(cnt[a[i]] == 0) num++;
        cnt[a[i]]++;
    }
    if(num != 2)
    {
        cout << "No\n";
        return;
    }
    vector<int> p;
    for(auto [x, y] : cnt)
    {
        p.push_back(y);
    }
    if(p[0] != p[1])
    {
        cout << "No\n";
        return;
    }
    cout << "Yes\n";
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
