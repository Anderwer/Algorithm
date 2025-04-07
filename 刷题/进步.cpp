#include <bits/stdc++.h>
#define int long long
using i64 = long long;
using namespace std;

template<typename T>
struct Fenwick
{
    int n;
    vector<T> a;

    Fenwick(int n_ = 0)
    {
        init(n_ + 1);
    }

    void init(int n_)
    {
        n = n_;
        a.assign(n, T{});
    }

    int lowbit(int x)
    {
        return x & -x;
    }

    void add(int pos, const T& val)
    {
        for(int i = pos; i < n; i += lowbit(i))
            a[i] = a[i] + val;
    }

    T internalQuery(int pos)
    {
        T res{};
        for(int i = pos; i; i -= lowbit(i))
            res = res + a[i];
        return res;  
    }

    T get(int l, int r)
    {
        return internalQuery(r) - internalQuery(l - 1);
    }
    
};

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    Fenwick<int> FT(n);
    for(int i = 1; i <= n; i++) 
    {
        int x; cin >> x;
        FT.add(i, x);
        a[i] = x;
    }  
    
    vector<int> res;
    int ans = 0;
    for(int i = 1; i <= q; i++)
    {
        int op; cin >> op;
        if(op == 1)
        {
            int x, y;
            cin >> x >> y;
            FT.add(x, -a[x]);
            FT.add(x, y);
            a[x] = y;
        }
        else if(op == 2)
        {
            int l, r;
            cin >> l >> r;
            res.push_back((FT.internalQuery(r) / 100) - (FT.internalQuery(l - 1) / 100));
        }
    }
    for(int i = 0; i < res.size(); i++)
        ans ^= (res[i] * (i + 1));
    cout << ans << "\n";
}

// 快速查询可修改前缀和
// Fenwick Tree 即可

signed main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--)
    {
        solve();
    }
    return 0;
}
