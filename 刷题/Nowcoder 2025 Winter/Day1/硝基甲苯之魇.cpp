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
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    vector<int> pre(n + 1, 0);
    map<int, vector<int>> mp; //用 map 存 [1, i] 的各个 xor 有多少种 i
    for(int i = 1; i <= n; i++)
    {
        pre[i] = pre[i - 1] ^ a[i];
        mp[pre[i]].push_back(i);
    }

    int ans = 0;
    ST st(a, n);
    for(int i = 1; i <= n; i++) //枚举左端点, 区间 [i, n] 一共只有 log 种 gcd
    {
        int cur_gcd = st.f[i][0]; //起始 gcd 为本身
        vector<array<int, 2>> pos; //记录区间 [i, n] 中的等价区间 [l, r], 当 pos ∈ [l, r] 时, 区间 [i, pos] 的 gcd 都不会改变

        int L = i;
        while(L <= n)
        {
            int l = L, r = n, res = 0;
            while(l <= r) 
            {
                int mid = (l + r) / 2;
                if(st.query(i, mid) < cur_gcd) r = mid - 1;
                else l = mid + 1, res = mid;
            }

            pos.push_back({L, res + 1}); //区间 [L, res] 的 gcd 相同
            L = res + 1;
            cur_gcd = gcd(cur_gcd, a[L]);
        }

        for(auto [l, r] : pos) //当 pos ∈ [l, res] 时, 区间 [i, pos] 的 gcd 都不会改变
        { 
            int GCD = st.query(i, l); //现在要在区间 [l, r] 中找异或和为 GCD 的右端点 x 有多少个
            int pointer = GCD ^ pre[i - 1]; // 由于 mp 里标记的是前缀异或和, 假设区间 [i, x] 的 xor == GCD, 则有 GCD == pre[x] ^ pre[i - 1], 因此转换 pointer = GCD ^ pre[i - 1]
            
            int res = lower_bound(mp[pointer].begin(), mp[pointer].end(), r) - lower_bound(mp[pointer].begin(), mp[pointer].end(), l); // 模拟二分统计即可
            ans += res;
        }
    }
    
    cout << ans - n << "\n";
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
