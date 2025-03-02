#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int k;
    cin >> k;
    vector<int> a(k + 1, 0);
    for(int i = 1; i <= k; i++)
    {
        int x; cin >> x;
        a[x]++;
    }
    for(int i = 1; i <= k; i++)
    {
        if((k - 2) % i == 0)
        {
            int m = (k - 2) / i;
            if(m == i && a[m] >= 2)
            {
                cout << i << " " << m << "\n";
                return;
            }
            if(m != i && a[m] >= 1 && a[i] >= 1)
            {
                cout << i << " " << m << "\n";
                return;
            }
        }
    }


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
