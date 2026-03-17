#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

const int N = 2e5 + 10;
int a[N];

void solve()
{
    int n, k;
    cin >> n >> k;
    for(int i = 1; i <= n; i++) cin >> a[i];
    int GCD = 0, ans = 0;
    for(int i = 1; i <= n; i++) GCD = gcd(GCD, a[i]);
    if(n == 1)
    {
        if(k <= a[1]) ans = k - 1;
        else ans = k;
        cout << ans << "\n";
        return;
    }
    else if(GCD == 1)
    {
        ans = n + k - 1;
        cout << ans << "\n";
        return;
    }
    else if(GCD > 1)
    {
        int T = k / (GCD - 1);
        if(k % (GCD - 1)) T++;
        T = min(T, n);
        ans = T + k - 1;
        cout << ans << "\n";
        return;
    }
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
此题关键 a[i] = a[i] - a[j] ,当a[i] >= a[j] 时
这个是辗转相减法 ,最终可以得到gcd(a[i], a[j]);
因此, 整个数组都会变为 gcd(a[1], a[2], a[3], ..., a[n])


特判当 n == 1 时, 如果 k <= a[1] , ans = k - 1
否则 ans = k

为了使mex_k 最大, 
如果数组中两个元素相差很大 , 那么 当 mex_k == a[i] - 1 时, mex_{k + 1} == a[i] + 1, ...
这样会让被跳过的数更少
因此需要让两个元素相差尽可能小
但是差值不能为0, 如果为0也会导致被跳过的数更少
此时再进行a[i] = a[i] + a[j] 的操作
把a 变为 {0, gcd, 2gcd, 3gcd, 4gcd, ...}

如果 a = {2, 8, 10}
那 mex = {0, 1, 3, 4, 5, 6, 7, 9, 11...}

经过操作后 gcd = 2
          a = {0, 2, 4}
那 mex = {1, 3, 5, 7, 8, 9, 10, 11, 12...}
可以看到更优

如果 gcd = 1时, a = {0, 1, 2, 3, 4, 5...}
mex = {n , n + 1, n + 2, n + 3...} 
所以mex_k = n + k - 1

当 gcd > 1 时
有 a = {0, gcd, 2gcd, 3gcd, 4gcd, 5gcd...}
   mex = {[1, gcd - 1], [gcd + 1, 2gcd - 1], [2gcd + 1, 3gcd - 1], ...}
   一个区间里有 (gcd - 1) - 1 + 1 = gcd - 1 个数
   先算mex_k 在第几个区间里 T = k / (gcd - 1) 向上取整
   然后一共有 n个区间, T = min(T, n)
   ans = T + k - 1
*/ 