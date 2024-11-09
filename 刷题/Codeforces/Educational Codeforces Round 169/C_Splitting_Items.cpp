#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 2e5 + 10;
int a[N];

void solve()
{
    int n, k;
    i64 A = 0, B = 0;
    cin >> n >> k;
    for(int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + 1 + n, greater<int>());
    for(int i = 1; i <= n; i++)
    {
        if(i & 1) continue;
        if(k >= a[i - 1] - a[i]) k -= a[i - 1] - a[i], a[i] = a[i - 1];
        else
        {
            a[i] += k;
            break;
        }
    }
    for(int i = 1; i <= n; i++)
    {
        if(i & 1) A += a[i];
        else B += a[i];
    }
    cout << A - B << "\n";
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
