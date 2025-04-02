#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int mod = 1e9 + 7;

struct ST //Max Min
{   
    const int logn = 23;
    const int Max = 1E9 + 10;
    const int Min = -1E9 - 10;
    vector<vector<int>> odd_max, odd_min, even_max, even_min, len;

    ST(vector<int>& a, int n)
    {
        odd_max.assign(n + 1, vector<int>(logn + 1));
        odd_min.assign(n + 1, vector<int>(logn + 1));
        even_max.assign(n + 1, vector<int>(logn + 1));
        even_min.assign(n + 1, vector<int>(logn + 1));
        len.assign(n + 1, vector<int>(logn + 1));

        for(int i = 1; i <= n; i++)
        {
            even_max[i][0] = odd_max[i][0] = Min;
            even_min[i][0] = odd_min[i][0] = Max;
            if(i % 2 == 0) even_max[i][0] = even_min[i][0] = a[i];
            else odd_max[i][0] = odd_min[i][0] = a[i];
        }

        for(int j = 1; j <= logn; j++)
        {
            for(int i = 1; i + (1 << j) - 1 <= n; i++)
            {
                even_max[i][j] = max(even_max[i][j - 1], even_max[i + (1 << (j - 1))][j - 1]);
                even_min[i][j] = min(even_min[i][j - 1], even_min[i + (1 << (j - 1))][j - 1]);
                odd_max[i][j] = max(odd_max[i][j - 1], odd_max[i + (1 << (j - 1))][j - 1]);
                odd_min[i][j] = min(odd_min[i][j - 1], odd_min[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    //[l][k] [r - (1 << k) + 1][k]
    bool query(int l, int r) // Max_odd < Min_even ||  Max_even < Min_odd 就是海浪
    {
        int k = __lg(r - l + 1);
        int Max_odd = max(odd_max[l][k], odd_max[r - (1 << k) + 1][k]);
        int Min_odd = min(odd_min[l][k], odd_min[r - (1 << k) + 1][k]);
        int Max_even = max(even_max[l][k], even_max[r - (1 << k) + 1][k]);
        int Min_even = min(even_min[l][k], even_min[r - (1 << k) + 1][k]);
        return (Max_odd < Min_even ||  Max_even < Min_odd);
    }
    
    void cal_len(int n)
    {
        for(int j = 1; j <= logn; j++)
        {
            for(int i = 1; i + (1 << j) - 1 <= n; i++)
            {
                len[i][j] = max(len[i][j - 1], len[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int query_len(int l, int r)
    {
        int k = __lg(r - l + 1);
        return max(len[l][k], len[r - (1 << k) + 1][k]);
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    ST st(a, n);
    vector<int> p(n + 1, 0);
    for(int L = 1, R = 1; R <= n; R++) //预处理 p[i] 和 len ST表
    {
        while(L <= R && st.query(L, R) == false) L++;
        p[R] = L; // 区间 [L, R] 为最长
        st.len[R][0] = R - L + 1;
    }
    st.cal_len(n);

    i64 ans = 0;
    for(i64 i = 1; i <= q; i++)
    {
        int L, R;
        cin >> L >> R;
        int x = lower_bound(p.begin() + 1 + L, p.begin() + 1 + R, L) - p.begin();
        i64 res = x - L;
        if(x <= R) res = max(res, (i64)st.query_len(x, R));
        ans = (ans + (i * res) % mod) % mod;
    }
    cout << ans << "\n";
}

// 合法区间有两种: [低, 高, 低, 高, ...] 和 [高, 低, 高, 低, ...]
// 对于[低, 高, 低, 高, ...] :此时 Max_odd < Min_even
// 对于[高, 低, 高, 低, ...] :此时 Max_even < Min_odd
// 查询一个区间[L, R]时, 由于区间合法判断是在区间中的相对奇偶性
// 注意到, 如果 L 是奇数, 那么相对奇偶性不变, 如果 L 是偶数, 那么相对奇偶性与真实奇偶性相反

// 因此, 我们可以维护 4 个 ST表, 分别查询 odd_max, odd_min, even_max, even_min 来O(1)判断一个区间是否合法
// 为了找到最长海浪, 考虑单次查询, 我们可以预处理出一个 p[i] 表示以 i 为右端点, p[i] 为左端点的最长海浪, 海浪区间为[p[i], i], 海浪长度为 i - p[i] + 1
// 因此, 在一次查询区间[L, R] 时, 由于 p[i] 递增, 可以二分找到第一个海浪右端点 x 使得 p[x] >= L, 则此时区间划分成两部分
// 左边的海浪为 [p[x], x], 而还有一种可能, 就是最长海浪在区间 [x, R] 中
// 这样分的原因是在区间[L, R]中如果随便选一个点 y, 可能 p[y] < L, 这样就脱离了查询范围, 而由于 p[i] 具有递增性, 则找到一个 x 后区间 [x, R] 中就不可能出现前面的问题
// 现在为了快速查找区间[x, R]中的最大海浪长度, 可以再建一个 ST表以便查询, len[i] 中存以 i 为右端点的最长海浪, 直接查询即可

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
