#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

int query(int a, int b)
{
    int res = 0;
    cout << "? " << a << " " << b << endl;
    cin >> res;
    return res;
}

void solve()
{
    int l = 2, r = 999, x = 0;
    while(l <= r)
    {
        int mid = (l + r) >> 1;
        int res = query(mid, mid);
        if(res == mid * mid) l = mid + 1;
        else x = mid, r = mid - 1;
    }
    cout << "! " << x << "\n";
}

int main()
{
    //std::ios::sync_with_stdio(false);
    //std::cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
