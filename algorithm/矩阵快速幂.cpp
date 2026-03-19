#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

// 矩阵快速幂模板
// 适用范围:
// 1. 线性递推
// 2. DP 状态转移矩阵
// 3. 图上路径计数 / 走 k 步转移
// 4. 任何可以写成 f_{t+1} = M * f_t 的问题
//
// 约定:
// 1. 矩阵大小为 n * n
// 2. 所有运算都在模 mod 下进行
// 3. 下标从 0 开始
//
// 常见用法:
// 1. 直接求 M^k
// 2. 求 M^k * 初始向量
//
// 说明:
// 1. 如果最终只需要 M^k * vec, 建议直接在快速幂过程中把矩阵作用到向量上
// 2. 这样通常比先完整求出 M^k 再乘向量常数更小

struct Matrix
{
    int n, mod;
    vector<int> a;

    Matrix() {}
    Matrix(int n_, int mod_, bool id = false)
    {
        init(n_, mod_, id);
    }

    void init(int n_, int mod_, bool id = false)
    {
        n = n_;
        mod = mod_;
        a.assign(n * n, 0);
        if(id)
        {
            for(int i = 0; i < n; i++) a[i * n + i] = 1 % mod;
        }
    }

    int* operator [](int x)
    {
        return &a[x * n];
    }

    const int* operator [](int x) const
    {
        return &a[x * n];
    }
};

Matrix mul(const Matrix& A, const Matrix& B)
{
    int n = A.n, mod = A.mod;
    Matrix BT(n, mod), C(n, mod);

    for(int i = 0; i < n; i++)
    {
        const int* p = B[i];
        for(int j = 0; j < n; j++) BT[j][i] = p[j];
    }

    for(int i = 0; i < n; i++)
    {
        const int* x = A[i];
        for(int j = 0; j < n; j++)
        {
            const int* y = BT[j];
            __int128 sum = 0;
            for(int k = 0; k < n; k++) sum += (__int128)x[k] * y[k];
            C[i][j] = (int)(sum % mod);
        }
    }
    return C;
}

vector<int> mul(const Matrix& A, const vector<int>& v)
{
    int n = A.n, mod = A.mod;
    vector<int> res(n, 0);

    for(int i = 0; i < n; i++)
    {
        const int* p = A[i];
        __int128 sum = 0;
        for(int j = 0; j < n; j++) sum += (__int128)p[j] * v[j];
        res[i] = (int)(sum % mod);
    }

    return res;
}

Matrix qpow(Matrix a, i64 b)
{
    Matrix res(a.n, a.mod, true);
    while(b)
    {
        if(b & 1) res = mul(res, a);
        a = mul(a, a);
        b >>= 1;
    }
    return res;
}

// 直接计算 M^k * vec
vector<int> qpow_apply(Matrix a, i64 b, vector<int> vec)
{
    while(b)
    {
        if(b & 1) vec = mul(a, vec);
        b >>= 1;
        if(b) a = mul(a, a);
    }
    return vec;
}

/*
使用示例1: 求矩阵 M 的 k 次幂
int n = ...;
int mod = ...;
Matrix M(n, mod);
... // 给 M 赋值
i64 k = ...;
Matrix P = qpow(M, k);

使用示例2: 求 M^k * 初始向量 f
int n = ...;
int mod = ...;
Matrix M(n, mod);
vector<int> f(n);
... // 给 M 和 f 赋值
i64 k = ...;
vector<int> ans = qpow_apply(M, k, f);

说明:
1. 若状态转移是 f_{t+1} = M * f_t, 那么第 k 步通常是 M^k * f_0
2. 若初始状态就是第 1 步, 还是第 0 步, 要按题意自行对应
3. 如果矩阵维数不大、步数很大, 这是最常用的标准模板
*/