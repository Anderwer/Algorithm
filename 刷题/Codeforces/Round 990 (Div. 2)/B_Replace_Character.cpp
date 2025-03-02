#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<char> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    map<char, int> cnt;
    for(int i = 1; i <= n; i++) cnt[a[i]]++;
    int mx = 0, mn = 1e9;
    char mxx, mnn;
    for(auto [x, y] : cnt)
    {
        if(y >= mx)
        {
            mx = y;
            mxx = x;
        }
        if(y < mn)
        {
            mn = y;
            mnn = x;
        }
    }
    for(int i = 1; i <= n; i++)
    {
        if(a[i] == mnn)
        {
            a[i] = mxx;
            break;
        }
    }
    for(int i = 1; i <= n; i++) cout << a[i];
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
