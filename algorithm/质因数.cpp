#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

// 质数与质因数模板集合
// 包含:
// 1. 线性筛
// 2. 埃氏筛
// 3. 单个数质因数分解
// 4. 约数个数
// 5. 约数和
// 6. 欧拉函数
//
// 适用范围:
// 1. 预处理 1..N 的质数
// 2. 多次做质因数分解
// 3. 数论题中的基础因子处理

struct PrimeTable
{
    int n;
    vector<int> primes;
    vector<int> minp;
    vector<bool> isPrime;

    PrimeTable() {}
    PrimeTable(int n_)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        primes.clear();
        minp.assign(n + 1, 0);
        isPrime.assign(n + 1, false);
    }

    // 线性筛
    void eulerSieve()
    {
        fill(minp.begin(), minp.end(), 0);
        fill(isPrime.begin(), isPrime.end(), false);
        primes.clear();

        if(n >= 2)
        {
            for(int i = 2; i <= n; i++)
            {
                if(minp[i] == 0)
                {
                    minp[i] = i;
                    primes.push_back(i);
                    isPrime[i] = true;
                }
                for(auto p : primes)
                {
                    if(1LL * i * p > n) break;
                    minp[i * p] = p;
                    if(i % p == 0) break;
                }
            }
        }
    }

    // 埃氏筛
    void eratosthenes()
    {
        primes.clear();
        fill(isPrime.begin(), isPrime.end(), true);
        fill(minp.begin(), minp.end(), 0);

        if(n >= 0) isPrime[0] = false;
        if(n >= 1) isPrime[1] = false;

        for(int i = 2; i <= n; i++)
        {
            if(isPrime[i])
            {
                primes.push_back(i);
                minp[i] = i;
                if(1LL * i * i <= n)
                {
                    for(int j = i * i; j <= n; j += i)
                    {
                        isPrime[j] = false;
                        if(minp[j] == 0) minp[j] = i;
                    }
                }
            }
        }
    }

    bool checkPrime(int x) const
    {
        if(x < 0 || x > n) return false;
        return isPrime[x];
    }

    // 使用预处理好的质数表分解
    // 返回 (质因子, 指数)
    vector<pair<i64, int>> factorize(i64 x) const
    {
        vector<pair<i64, int>> res;
        if(x <= 1) return res;

        for(auto p : primes)
        {
            if(1LL * p * p > x) break;
            if(x % p == 0)
            {
                int cnt = 0;
                while(x % p == 0)
                {
                    x /= p;
                    cnt++;
                }
                res.push_back({p, cnt});
            }
        }
        if(x > 1) res.push_back({x, 1});
        return res;
    }

    // 求 x 的不同质因子
    vector<i64> getPrimeFactors(i64 x) const
    {
        vector<i64> res;
        auto fac = factorize(x);
        for(auto [p, c] : fac) res.push_back(p);
        return res;
    }
};


// 不依赖筛表的单个数分解
struct Factorizer
{
    // 返回 (质因子, 指数)
    static vector<pair<i64, int>> factorize(i64 x)
    {
        vector<pair<i64, int>> res;
        if(x <= 1) return res;

        for(i64 p = 2; p * p <= x; p++)
        {
            if(x % p == 0)
            {
                int cnt = 0;
                while(x % p == 0)
                {
                    x /= p;
                    cnt++;
                }
                res.push_back({p, cnt});
            }
        }
        if(x > 1) res.push_back({x, 1});
        return res;
    }

    // 返回所有不同质因子
    static vector<i64> getPrimeFactors(i64 x)
    {
        vector<i64> res;
        auto fac = factorize(x);
        for(auto [p, c] : fac) res.push_back(p);
        return res;
    }

    // 约数个数
    static i64 divisorCount(i64 x)
    {
        auto fac = factorize(x);
        i64 ans = 1;
        for(auto [p, c] : fac) ans *= (c + 1);
        return ans;
    }

    // 约数和
    static i64 divisorSum(i64 x)
    {
        auto fac = factorize(x);
        i64 ans = 1;
        for(auto [p, c] : fac)
        {
            i64 cur = 1, sum = 1;
            for(int i = 1; i <= c; i++)
            {
                cur *= p;
                sum += cur;
            }
            ans *= sum;
        }
        return ans;
    }

    // 欧拉函数
    static i64 phi(i64 x)
    {
        i64 ans = x;
        for(i64 p = 2; p * p <= x; p++)
        {
            if(x % p == 0)
            {
                ans = ans / p * (p - 1);
                while(x % p == 0) x /= p;
            }
        }
        if(x > 1) ans = ans / x * (x - 1);
        return ans;
    }
};

/*
使用示例:

1. 预处理质数
PrimeTable pt(1000000);
pt.eulerSieve();

2. 判断质数
if(pt.checkPrime(x)) ...

3. 利用筛表做分解
auto fac = pt.factorize(x);
for(auto [p, c] : fac)
{
    cout << p << " " << c << "\n";
}

4. 单个数直接分解
auto fac = Factorizer::factorize(x);

5. 约数个数 / 约数和 / 欧拉函数
cout << Factorizer::divisorCount(x) << "\n";
cout << Factorizer::divisorSum(x) << "\n";
cout << Factorizer::phi(x) << "\n";

说明:
1. 若需要频繁分解很多数, 推荐先筛质数, 再调用 PrimeTable::factorize
2. 若只分解少量单个数, 直接用 Factorizer 即可
3. 若 x 很大(例如接近 1e18), 朴素分解会慢, 需要更高级算法
*/