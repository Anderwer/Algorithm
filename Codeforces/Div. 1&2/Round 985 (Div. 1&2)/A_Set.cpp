#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    i64 l, r, k;
    cin >> l >> r >> k;
    cout << max(0LL, (r / k) - l + 1) << "\n";
    
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
1 2 3 4 5 6 7 8 9 10, k = 3

对于 区间[L, R], 找到一个数 x 使得 x * k > R, 则这个数后面的都不符合操作
则找第一个满足 x * k > R 的 x
x = [R / k]取下界
*/