#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

bool check(i64 x, i64 k)
{
    i64 res = x - (int)sqrtl(x);
    return res >= k;
}

void solve()
{
    i64 k;
    cin >> k;
    i64 l = 1, r = 2e18, ans = 0;
    while(l <= r)
    {
        i64 mid = (l + r) / 2;
        if(check(mid, k)) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    cout << ans << "\n";
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

/*
打表发现 : 下标为 1^2, 2^2, 3^2, 4^2, ... 的位置是关灯状态
即 1, 4, 9, 16, 25, 36 ...
假设答案为 n
一共有 n - k 个位置是关灯的
则 pos >= (n - k)^2
使n 最小
则有 n <= (n - k) ^ 2

开平方得 : n - √n >= k
用二分查找搜最小的 n
*/