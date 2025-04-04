#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> c(n + 1), a(m + 1);
    for(int i = 1; i <= n; i++) cin >> c[i];
    for(int i = 1; i <= m; i++) cin >> a[i];


}

// 首先, 看到 (a - b)^2 最小, 则应该对数组进行排序
// 转化成有序序列后, 从中选择 m + x 根筷子, 使得不舒适度的和最小
// 

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
