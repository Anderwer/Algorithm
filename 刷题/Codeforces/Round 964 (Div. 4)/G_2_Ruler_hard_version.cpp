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
    int l = 1, r = 999;
    while(l < r)
    {
        int mid_l = l + (r - l) / 3;
        int mid_r = r - (r - l) / 3;
        int res = query(mid_l, mid_r);

        if(res == mid_l * mid_r) l = mid_r + 1;
        else if(res == (mid_l + 1) * (mid_r + 1)) r = mid_l;
        else l = mid_l + 1, r = mid_r;
    }
    
    cout << "! " << l << "\n";
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

/*
由于 log2(1000) = 10, 不行
而 log3(1000) = 7, 考虑三分

如果 a < b < x, 则 res = a * b
如果 a < x <= b, 则 res = a * (b + 1)
如果 x <= a < b, 则 res = (a + 1) * (b + 1)

所以一次查询可以分成3个区间: (1, a]  (a, b]  (b, 999]
注意特判当 x 只剩2个可能值的时候
*/