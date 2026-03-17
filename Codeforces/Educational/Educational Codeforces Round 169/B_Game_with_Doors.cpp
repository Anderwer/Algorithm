#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
int cnt[110];

void solve()
{
    int l, r, L, R;
    cin >> l >> r >> L >> R;
    for(int i = 1; i <= 105; i++) cnt[i] = 0;
    for(int i = l; i <= r; i++) cnt[i]++;
    for(int i = L; i <= R; i++) cnt[i]++;
    int ans = 0;
    for(int i = min(l, L); i <= max(r, R); i++)
        if(cnt[i] == 2) ans++;
    if(l == L) ans--;
    if(r == R) ans--;
    cout << ans + 1 << "\n";
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
