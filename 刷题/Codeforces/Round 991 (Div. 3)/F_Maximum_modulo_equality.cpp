#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

struct ST //gcd
{
    vector<vector<int>> f;

    ST(vector<int>& a, int n)
    {
        const int logn = 23;
        f.assign(n + 1, vector<int>(logn + 1, 0));

        for(int i = 1; i <= n; i++) f[i][0] = a[i];
        for(int j = 1; j <= logn; j++)
        {
            for(int i = 1; i + (1 << j) - 1 <= n; i++)
            {
                f[i][j] = gcd(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int query(int l, int r)
    {
        int k = __lg(r - l + 1);
        return gcd(f[l][k], f[r - (1 << k) + 1][k]);
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    vector<int> b(n + 1);
    for(int i = 1; i <= n - 1; i++) b[i] = abs(a[i] - a[i + 1]);
    ST ans(b, n - 1);
    
    while(q--)
    {
        int l, r; cin >> l >> r;
        if(l == r) cout << 0 << " ";
        else cout << ans.query(l, r - 1) << " "; // 因为查询的是 差值的 gcd, 因此是 r - 1, 少一个元素
    }
    
    cout << "\n";
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
要求区间 a[l, r] 的同余模数, 相当于 a[l, r] 在同一个等差数列里, 
先算出相邻两个数的差值, [l, r] 中所有差值的gcd 就是最大的模数
证明:
引理(1) : 设 a > b, 则有 a % (a - b) == b % (a - b)
证明: 设 p = a - b, a = kp + q
则有 b = a - (a - b) = (k - 1)p + q
因此 a % p == b % p == q

引理(2) : 设 a > b, 则 a 和 b 对 a - b 的所有因数同余
证明: 设p = a - b, a = kp + q, b = (k - 1)p + q
设 p 中的一个因数为 p0
因为 kp | p 且 (k - 1)p | p
所以 kp | p0 且 (k - 1)p | p0
因此 a % p0 == b % p0 == q

现在, 区间 a[l, r] 可以拆成 a[l], a[l + 1] ; a[l + 1], a[l + 2]; ... ; a[r - 1], a[r]
如果区间所有数都同余, 那么有 
a[l] 与 a[l + 1]同余 ----> |a[l] - a[l + 1]| 是模数 m 的一个因数
a[l + 1] 与 a[l + 2]同余 ----> |a[l + 1] - a[l + 2]| 是模数 m 的一个因数
...
a[r - 1] 与 a[r]同余 ----> |a[r - 1] - a[r]| 是模数 m 的一个因数

因此, 满足这些条件的 m 就是这些因数的公因数, 由于题中求最大的 m, 则 m 就是这些因数的最大公因数
因此, 得出结论 m = gcd(|a[l] - a[l + 1]|, |a[l + 1] - a[l + 2]|, ..., |a[r - 1] - a[r]|)
可以用 一个 ST表 维护区间gcd, 以供O(1)查询
*/