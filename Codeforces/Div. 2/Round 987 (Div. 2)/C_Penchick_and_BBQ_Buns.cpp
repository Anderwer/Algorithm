#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1, 0);
    if(n % 2 == 0)
    {
        for(int i = 1; i <= n / 2; i++) a[2 * i - 1] = a[2 * i] = i;
    }
    else
    {
        if(n < 27)
        {
            cout << -1 << "\n";
            return;
        }
        int p = n - 26;
        a[p] = a[p + 16] = a[p + 25] = 1;
        a[p + 1] = a[p + 26] = 2;
        int cur = 3;
        for(int i = 1; i < n; i++)
        {
            if(a[i] == 0 && a[i + 1] == 0)
            {
                a[i] = a[i + 1] = cur;
                cur++;
                i++;
            }
        }
    }
    for(int i = 1; i <= n; i++) cout << a[i] << " ";
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
