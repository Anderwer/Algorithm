#include <bits/stdc++.h>
#define int long long
using i64 = long long;
using namespace std;
const int N = 1e5 + 10;
int x[N];

void solve()
{
    int n, q;
    cin >> n >> q;
    for(int i = 1; i <= n; i++) cin >> x[i];
    map<i64, int> cnt;
    for(int i = 1; i < n; i++) cnt[i * (n - i)] += (x[i + 1] - x[i] - 1);
    for(int i = 1; i <= n; i++) cnt[(i - 1) * (n - i) + (n - 1)]++;
    while(q--)
    {
        i64 k;
        cin >> k;
        cout << cnt[k] << " ";
    }
    cout << "\n";
} 
signed main()
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

/*
注意到,  在任意一个区间(x[i], x[i + 1])之间的点, 它们覆盖的线段数都相同
假设这个区间左边有 i 个点(包含区间左端点), 右边有 n - i 个点, 通过简单计数可知区间内的点覆盖的线段数为 left * right 即 i * (n - i)

再考虑区间端点
假设一个点的下标为 i , 那么它左边有 i - 1 个点, 右边有 n - i 个点, 那么不考虑以 x[i]作为区间左右端点时覆盖的数量为 (i - 1) * (n - i)
考虑以 x[i] 为区间左端点时, 有(i - 1) 个线段, 考虑以 x[i] 为区间右端点时, 有(n - i) 个线段
因此, 对于一个 x[i], 它的线段覆盖数为 (i - 1) * (n - i) + (n - 1)

之后可以用一个map 记录 , 以 覆盖了多少条线段为key , 有多少个点为 value
*/