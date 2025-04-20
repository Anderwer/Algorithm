
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
// 区间 [L, R] 的 gcd 等于 a[L] 和所有相邻两数之差绝对值的 gcd
// gcd(a[L], a[L + 1], ...) = gcd(a[L], |a[L] - a[L + 1]|, |a[L + 1] - a[L + 2]|, ...)
