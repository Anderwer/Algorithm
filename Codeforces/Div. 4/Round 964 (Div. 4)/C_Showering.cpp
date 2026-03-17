#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 2e5 + 10;
int l[N], r[N];

void solve()
{
    int n, s, m;
    cin >> n >> s >> m;
    for(int i = 1; i <= n; i++) cin >> l[i] >> r[i];
    
    bool ans = false;
    for(int i = 0; i < n; i++)
    {
        if(l[i + 1] - r[i] >= s) ans = true;
    }
    if(m - r[n] >= s) ans = true;

    if(ans == true) cout << "YES\n";
    else cout << "NO\n";
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
l[i + 1] - r[i]
*/