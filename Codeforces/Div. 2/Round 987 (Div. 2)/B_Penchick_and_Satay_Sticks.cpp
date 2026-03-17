#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    bool flag = true;
    for(int i = 1; i < n; i++)
    {
        if(a[i] == i) continue;
        if(a[i] == i + 1 && a[i + 1] == i)
        {
            swap(a[i], a[i + 1]);
            continue;
        }
        else flag = false;
    }
    if(flag == true) cout << "YES\n";
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
