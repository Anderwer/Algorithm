#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

bool query(int l, int r)
{
    bool res;
    cout << "? " << l << " " << r << endl;
    cin >> res;
    return res;
}

void solve()
{
    int n;
    cin >> n;

    if(query(1, n / 4) == query(n / 4 + 1, n / 2)) //res1 == res2, 说明 1 在 [n / 2 + 1, n] 中
    {
        if(query(n / 2 + 1, n) == true) // k > n / 2
        {
            int l = 1, r = n / 2;
            while(l <= r)
            {
                int mid = (l + r) / 2;
                if(query(mid, n) == true) r = mid - 1;
                else l = mid + 1;
            }
            cout << "! " << n - (l - 1) + 1 << endl;
        }
        else // k <= n / 2
        {
            int l = 1, r = n / 2;
            while(l <= r)
            {
                int mid = (l + r) / 2;
                if(query(mid, n / 2) == true) l = mid + 1;
                else r = mid - 1;
            }
            cout << "! " << n / 2 - r + 1 << endl;
        }
    }
    else// 1 在 [1, n / 2] 中
    {
        if(query(1, n / 2) == true) // k > n / 2
        {
            int l = n / 2 + 1, r = n;
            while(l <= r)
            {
                int mid = (l + r) / 2;
                if(query(1, mid) == true) l = mid + 1;
                else r = mid - 1;
            }
            cout << "! " << r + 1 << endl;
        }
        else // k <= n / 2
        {
            int l = n / 2 + 1, r = n;
            while(l <= r)
            {
                int mid = (l + r) / 2;
                if(query(n / 2 + 1, mid) == true) r = mid - 1;
                else l = mid + 1;
            }
            cout << "! " << l - n / 2 << endl;
        }
    }
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
