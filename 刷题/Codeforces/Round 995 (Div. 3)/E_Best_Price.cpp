#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
int n, k;

i64 check(vector<int>& a, vector<int>& b, int price)
{
    i64 a_num = n - (lower_bound(a.begin(), a.end(), price) - a.begin());
    i64 b_num = n - (lower_bound(b.begin(), b.end(), price) - b.begin());
    if(b_num - a_num > k) return 0;
    return b_num * price;
}

void solve()
{
    cin >> n >> k;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i];

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    i64 ans = 0;
    for(int i = 0; i < n; i++)
    {
        ans = max(check(a, b, a[i]), ans);
        ans = max(check(a, b, b[i]), ans);
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
贪心发现, price 定价一定是 a[i] 或者是 b[i] 中的某一个
因为如果是在中间值的话, price 可以提高而没有负面影响

因此, 选择枚举a[i] 和 b[i] 作为price, 然后二分找
给数组 a 和 b 排序
对数组 b 二分, 找的是满足 b[i] >= price 的人数 b_num
对数组 a 二分, 找的是满足 a[i] >= price 的人数 a_num
b_num - a_num 则为给差评的人数
判断这个是否 <= k 即可
*/