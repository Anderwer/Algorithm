#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 2e5 + 10;
int a[N];

void solve()
{
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    a[0] = a[n + 1] = 0;

    for(int i = 1; i <= n / 2; i++)
    {
        int num1 = (a[i] == a[i - 1]) + (a[n - i + 1] == a[n - i + 2]);
        swap(a[i], a[n - i + 1]);
        int num2 = (a[i] == a[i - 1]) + (a[n - i + 1] == a[n - i + 2]);
        if(num2 < num1) continue;
        else swap(a[i], a[n - i + 1]);
    }
    int cnt = 0;
    for(int i = 1; i < n; i++) if(a[i] == a[i + 1]) cnt++;
    cout << cnt << "\n";
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
