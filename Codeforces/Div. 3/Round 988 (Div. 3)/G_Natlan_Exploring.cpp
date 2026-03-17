#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int p = 998244353;

struct Prime
{
    const static int N = 1E6 + 10;
	bitset<N> vis;
	vector<int> P;

	void Erat_Prime() //埃氏筛 O(nloglogn), bitset优化后小于 O(n)
    {
        vis.set();
        vis[0] = vis[1] = 0;
        for(int i = 2; i * i < N; i++) if(vis[i]) for(int j = i << 1; j < N; j += i) vis[j] = 0;
        for(int i = 2; i < N; i++) if(vis[i]) P.push_back(i);
    }

    void Euler_Prime() //欧拉筛 O(n)
    {
        vis.set();
        vis[0] = vis[1] = 0;
        int cnt = 0;
        for(int i = 2; i < N; i++)
        {
            if(vis[i]) P.push_back(i), cnt++;
            for(int j = 0; j < cnt && i * P[j] < N; j++)
            {
                vis[i * P[j]] = 0;
                if(i % P[j] == 0) break;
            }
        }
    }

    vector<int> Erat_gcd(int x) //配合埃氏筛获取质因数 O(√(n / lnn))
    {
        vector<int> res;
        if(x == 2 || x == 3)
        {
            res.push_back(x);
            return res;
        }
        for(auto v : P)
        {
            if(v * v > x) break;
            if(x % v == 0)
            {
                res.push_back(v);
                while(x % v == 0) x /= v;
            }
        }
        if(x != 1) res.push_back(x);
        return res;
    }

    vector<int> gcdcnt(int x) //朴素获取质因数 O(√n)
    {
        vector<int> res;
        for(int i = 2; i * i <= x; i++)
        {
            if(x % i == 0)
            {
                while(x % i == 0) x /= i;
                res.push_back(i);
            }
        }
        if(x != 1) res.push_back(x);
        return res;
    }

};

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    Prime pr;
    pr.Erat_Prime();
    vector<i64> f(n + 1, 0);
    vector<i64> g(pr.N + 1, 0);

    f[1] = 1; //dp 初始化
    for(int i = 1; i <= n; i++)
    {
        vector<int> P = pr.Erat_gcd(a[i]);
        int cnt = P.size();
        for(int j = 1; j < (1 << cnt); j++) //用二进制枚举选了哪些质因子
        {
            i64 cur = 1, num = 0; //cur计算当前枚举的质因子乘积, num 计算当前选了多少个质因子
            for(int k = 0; k < cnt; k++)
            {
                if((j & (1 << k)) > 0) // 判断每一位是 0 / 1
                {
                    cur = cur * P[k];
                    num++;
                }
            }
            if(num % 2 == 1) f[i] = (f[i] + g[cur]) % p;
            else f[i] = (f[i] - g[cur] + p) % p;
        }

        for(int j = 1; j < (1 << cnt); j++) //上方更新完 f[i] 之后再反手更新 g[x]
        {
            i64 cur = 1;
            for(int k = 0; k < cnt; k++)
            {
                if((j & (1 << k)) > 0) cur = cur * P[k];
            }
            g[cur] = (g[cur] + f[i]) % p;
        }
    }
    cout << f[n] << "\n";
}   

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
    return 0;
}

/*
对于求方案数, 很容易想到 O(n2) 的转移, 设 f[i] 为从 1 到 i 的方案数
则有 f[i] = Σ f[j], 其中 j < i 且 gcd(a[i], a[j]) != 1

考虑对 a[i] 进行质因数分解, 因此在一个位置 i 时, 假设 a[i] 含有质因子x, f[i] 可以从前面所有含有质因子 x 的 a[j] 转移过来
但是如果枚举 j, 则最坏也会被卡到 O(n2), 因此考虑优化
设 g[x] 为 到位置 i 时, 用质因数 x 走到位置 i 的方案数, 即 g[x] = Σ f[j], 其中 j ∈ [1, i - 1] 且 x ∈ p{a[j]}, p{}是一个数的质因数集合

则每次转移有 f[i] = Σ g[x], 其中 x ∈ p{a[i]}, 但要注意, 这些 g[x] 可能会算重, 需要用到容斥原理
如序列 {2, 6, 3, 4, 6}
它们对应的质因子分别是 [{2}, {2, 3}, {3}, {2}, {2, 3}]
在转移到 f[5] 的时候, 由于 a[5] 的质因子是 {2, 3}, 因此 f[5] = g[2] + g[3]
f[5] += g[2] 的意义是 a[1], a[2], a[4] 可以连向 a[5]
f[5] += g[3] 的意义是 a[2], a[3] 可以连向 a[5]
因此注意到, 上面的 a[2] 连向 a[5] 被算重了, 我们要减去 g[2 * 3], 这就是容斥原理, 具体实现见代码

*/