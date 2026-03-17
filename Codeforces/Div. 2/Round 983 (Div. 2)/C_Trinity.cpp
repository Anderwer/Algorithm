#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int N = 2e5 + 10;
int a[N];

void solve()
{
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + 1 + n);
    int i = 1, ans = 1e9;
    for(int j = 3; j <= n; j++) //枚举最大值
    {
        while(i + 2 <= j && a[i] + a[i + 1] <= a[j]) i++;
        ans = min(ans, n - (j - i + 1));
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t = 1;
    cin >> t;
    while(t--) solve();
    return 0;
}
/*
假设 x < y < z < h
如果 (x, y, h) 满足三角形不等式
则有 x + y > h ---->    x + y > z
又因为 x + z > y, y + z > x
所以 (x, y, h) ----> (x, y, z)

将整个 a 排序, 由上面的规律可得, 让两个最小值相加 > 最大值即可
即 a[1] + a[2] > a[n]
我们假设第一小的是 a[i], 第二小的是 a[i + 1], 最大值是 a[j]
则要满足 a[i] + a[i + 1] > a[j], 这样区间 [i, j] 内的都满足, 要修改的则是 n - len([i, j]) 数量
因此, 我们可以枚举最大值 a[j], 找到一个符合的最左边的 i, 计算 ans最小值
由于数组已经有序, 我们可以持续向右更新 i 的值, 类似于双指针

*/