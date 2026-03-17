#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

// FFT 模板
// 适用范围:
// 1. 多项式卷积
// 2. 大整数乘法(需要自行处理进位)
// 3. 实数卷积 / 整数卷积(结果四舍五入)
//
// 约定:
// 1. 传入的多项式系数从 0 下标开始
// 2. multiply(a, b) 返回卷积后的系数数组 c
// 3. 若 a 的长度为 n, b 的长度为 m, 则 c 的长度为 n + m - 1
//
// 说明:
// 1. FFT 使用复数实现, 会有浮点误差
// 2. 若题目要求严格模意义卷积, 请优先使用 NTT

struct FFT
{
    using cd = complex<double>;
    const double PI = acos(-1.0);

    void fft(vector<cd>& a, int type)
    {
        int n = (int)a.size();

        for(int i = 1, j = 0; i < n; i++)
        {
            int bit = n >> 1;
            for(; j & bit; bit >>= 1) j ^= bit;
            j ^= bit;
            if(i < j) swap(a[i], a[j]);
        }

        for(int len = 2; len <= n; len <<= 1)
        {
            double ang = 2 * PI / len * type;
            cd wn(cos(ang), sin(ang));
            for(int i = 0; i < n; i += len)
            {
                cd w(1, 0);
                int half = len >> 1;
                for(int j = 0; j < half; j++)
                {
                    cd x = a[i + j];
                    cd y = w * a[i + j + half];
                    a[i + j] = x + y;
                    a[i + j + half] = x - y;
                    w *= wn;
                }
            }
        }

        if(type == -1)
        {
            for(int i = 0; i < n; i++) a[i] /= n;
        }
    }

    vector<i64> multiply(const vector<i64>& a, const vector<i64>& b)
    {
        if(a.empty() || b.empty()) return {};

        int n = (int)a.size();
        int m = (int)b.size();
        int len = 1;
        while(len < n + m - 1) len <<= 1;

        vector<cd> A(len), B(len);
        for(int i = 0; i < n; i++) A[i] = cd((double)a[i], 0);
        for(int i = 0; i < m; i++) B[i] = cd((double)b[i], 0);

        fft(A, 1);
        fft(B, 1);
        for(int i = 0; i < len; i++) A[i] *= B[i];
        fft(A, -1);

        vector<i64> c(n + m - 1);
        for(int i = 0; i < n + m - 1; i++)
        {
            c[i] = (i64)llround(A[i].real());
        }
        return c;
    }

    vector<double> multiply(const vector<double>& a, const vector<double>& b)
    {
        if(a.empty() || b.empty()) return {};

        int n = (int)a.size();
        int m = (int)b.size();
        int len = 1;
        while(len < n + m - 1) len <<= 1;

        vector<cd> A(len), B(len);
        for(int i = 0; i < n; i++) A[i] = cd(a[i], 0);
        for(int i = 0; i < m; i++) B[i] = cd(b[i], 0);

        fft(A, 1);
        fft(B, 1);
        for(int i = 0; i < len; i++) A[i] *= B[i];
        fft(A, -1);

        vector<double> c(n + m - 1);
        for(int i = 0; i < n + m - 1; i++)
        {
            c[i] = A[i].real();
        }
        return c;
    }
};

/*
使用示例:

1. 整数卷积
vector<i64> a = {1, 2, 3};
vector<i64> b = {4, 5, 6};
FFT fft;
auto c = fft.multiply(a, b);
// c = {4, 13, 28, 27, 18}

2. 大整数乘法(自行处理进位)
string s, t;
cin >> s >> t;
vector<i64> a(s.size()), b(t.size());
for(int i = 0; i < (int)s.size(); i++) a[s.size() - 1 - i] = s[i] - '0';
for(int i = 0; i < (int)t.size(); i++) b[t.size() - 1 - i] = t[i] - '0';
FFT fft;
auto c = fft.multiply(a, b);

// 然后手动处理进位即可

注意:
1. FFT 有浮点误差, 系数过大时要小心
2. 若模数卷积且模数合适, 优先用 NTT
*/