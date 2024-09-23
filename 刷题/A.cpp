#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

const int N = 105;
int a[N];

void solve()
{
    int n, k;
    cin >> n >> k;
    for(int i = 1; i <= n; i++) cin >> a[i];
    int ans = 0, now = 0;
    for(int i = 1; i <= n; i++)
    {
        if(a[i] >= k) now += a[i];
        else if(a[i] == 0 && now)
        {
            ans++;
            now--;
        }
    }
    cout << ans << "\n";
}

int main() 
{
    int t = 1;
    cin >> t;
    while(t--) solve();
    return 0;
}