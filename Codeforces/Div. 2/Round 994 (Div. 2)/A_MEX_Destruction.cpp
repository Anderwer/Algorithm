#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 2, 0);
    for(int i = 1; i <= n; i++) cin >> a[i];
    
    int cnt = 0;
    for(int i = 1; i <= n; i++)
    {
        if(a[i - 1] == 0 && a[i] != 0) cnt++;
    }
    if(cnt == 0) cout << 0 << "\n";
    else if(cnt == 1) cout << 1 << "\n";
    else cout << 2 << "\n";
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
