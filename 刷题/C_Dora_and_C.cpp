#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int N = 1e5 + 10;
int a[N];

void solve()
{
    int n, A, B;
    cin >> n >> A >> B;
    for(int i = 1; i <= n; i++) cin >> a[i];
    int g = gcd(A, B);
    for(int i = 1; i <= n; i++) a[i] %= g;
    sort(a + 1, a + 1 + n);
    int ans = a[n] - a[1];
    for(int i = 1; i < n; i++) ans = min(ans, a[i] + g - a[i + 1]);
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
操作可以对一个数 +a 或者 +b, 由于可以操作无限次, 这两个操作等价于对一个数 +gcd(a, b) 或者 -gcd(a, b)
因此, 我们可以把数组中的每个数变成在 [0, gcd(a,b)) 之间的数, 这样能保证所有数都最小

之后, 问题就等价于对数组中的每一个数都可以加任意多次 gcd(a, b), 求极差最小值
我们可以把数组排序, 并且让 a[i] + gcd(a, b), 然后取 ans = min(a[i] + gcd(a, b) - a[i + 1])
贪心的想, 数组中的每一个元素都可以成为最大值或最小值, 我们排完序之后可以让相邻两个元素的差最小,
然后再让左边的那个 +gcd 变为最大值, 右边的是最小值, 类似于破环成链
*/