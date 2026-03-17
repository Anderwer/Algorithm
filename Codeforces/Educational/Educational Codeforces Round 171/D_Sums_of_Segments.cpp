#include <bits/stdc++.h>
#define int long long
using namespace std;
using i64 = long long;
const int N = 3e5 + 10;
int n;
int a[N];
i64 f[N], s[N], pre[N], b_pre[N];

void init()
{
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++)
    {
        f[i] = f[i - 1] + n - i + 1;
        s[i] = s[i - 1] + a[i];
        pre[i] = pre[i - 1] + s[i];
    }
    b_pre[1] = pre[n];
    for(int i = 2; i <= n; i++) b_pre[i] = b_pre[i - 1] + pre[n] - pre[i - 1] - s[i - 1] * (n - i + 1LL);
}

pair<int, int> find(int x)
{
    int l = 1, r = n;
    int row = -1, col = -1; 
    if(x <= f[l]) row = l;
    else
    {
        while(l <= r)
        {
            int mid = (l + r) / 2;
            if(x <= f[mid]) row = mid, r = mid - 1;
            else l = mid + 1;
        }
    }
    col = n - f[row] + x;
    return make_pair(row, col);
}

i64 cal(int x)
{
    auto tmp = find(x);
    int row = tmp.first, col = tmp.second;
    i64 res = b_pre[row - 1] + pre[col] - pre[row - 1] - s[row - 1] * (col - row + 1LL);
    return res;
}
void solve()
{
    cin >> n;
    init();
    int q; cin >> q;
    while(q --)
    {
        int l, r; cin >> l >> r;
        cout << cal(r) - cal(l - 1) << "\n";
        //cout << find(r).first << " " << find(l - 1).first << "\n";
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t = 1;
    //cin >> t;
    while(t--) solve();
    return 0;
}
/*
设(i, j) 为 a[i ~ j]和
b[] :
(1, 1) (1, 2) (1, 3) (1, 4)  n
       (2, 2) (2, 3) (2, 4)  n - 1
              (3, 3) (3, 4)  n - 2
                     (4, 4)  n - 3

给定查询区间[l, r], 我们要确定一下 l 和 r 分别在 b[] 中的(i, j)
我们设 f[row] 为前 row 行的个数总和, 第 i 行有 n - i + 1 个元素, 则可以递推出 f[], 如果 f[row - 1] < l <= f[row], 则 l 在第 row 行, 我们可以利用二分快速获得
则我们通过 find 得到 l 和 r 对于的 (i, j)

我们用 s[] 获取一下 a[] 的前缀和, s[] 对应的是 b[] 中的第一行
设 pre[i] 为 b[] 第一行的前缀和
为了算 b[] 第 k 行的前缀和, 我们可以用 pre[n] - pre[1 ~ k - 1] - s[1 ~ k - 1] * (n - k + 1), 因此我们可以 O(1) 算出 b[] 的某一行的总和
设 b_pre[i] 为 b[] 前 i 行的总和, 利用上面的公式递推

当前假设询问区间[l, r] 中的 l - 1 对应b[] 中的 (row_l, col_l), r 对应 b[] 中的 (row_r, col_r)
则我们先计算 b[1 ~ r] = b_pre[row_r - 1] + pre[col_r] - pre[1 ~ row_r - 1] - s[1 ~ row_r - 1] * (col_r - row_r + 1)
再计算 b[1 ~ l - 1] = b_pre[row_l - 1] + pre[col_l] - pre[1 ~ row_l - 1] - s[1 ~ row_l - 1] * (col_l - row_l + 1)

对于一个区间[l, r], ans = b[1 ~ r] - b[1 ~ l - 1]
复杂度 O(n + q)
*/