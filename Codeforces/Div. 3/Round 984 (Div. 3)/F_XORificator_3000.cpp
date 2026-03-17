#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
i64 l, r, i, k;

i64 f(i64 x)
{
    i64 res;
    if(x % 4 == 0) res = x;
    else if(x % 4 == 1) res = 1;
    else if(x % 4 == 2) res = ((x + 3) / 4) * 4 - 1;
    else res = 0;
    return res; 
}

i64 f_B(i64 x)
{
    i64 now = x >> i << i | k; //先右移 i 位再左移 i位, 再加 k
    i64 cnt = 0;
    if(now <= x) cnt = x >> i;
    else cnt = (x >> i) - 1;
    i64 res = f(cnt) << i;
    if(cnt & 1) res |= k;
    return res;
}

void solve()
{
    cin >> l >> r >> i >> k;
    cout << ((f(r) ^ f(l - 1)) ^ (f_B(r) ^ f_B(l - 1))) << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t = 1;
    cin >> t;
    while(t--) solve();
    return 0;
}

/*
通过打表我们知道, 可以O(1) 计算出 从0到x的异或和
设 f(0, x) 为从0到x的异或和
    x % 4 == 0 时 f(0, x) = x
    x % 4 == 1 时 f(0, x) = 1
    x % 4 == 2 时 f(0, x) = ((x + 4 - 1) / 4) * 4 - 1
    x % 4 == 3 时 f(0, x) = 0

则 f(L, R) = f(0, R) ^ f(0, L - 1)

现在在区间[0, x] 中有两类数, 一种是 % 2^i != k的, 称为 A 类, 另一种是 % 2^i == k的, 称为 B 类
现在要求区间[L,R] 中所有 A 类数的异或和, 由异或交换性质可得:
f_A(L, R) = f(L, R) ^ f_B(L, R) = (f(0, R) ^ f(0, L - 1)) ^ (f_B(0, R) ^ f_B(0, L - 1))

现在问题是如何快速求得 f_B(0, x)
假设一个数为 num, 则要满足 num % 2^i == k, 就得保证 num 在二进制下的第 0 位到第 i 位和 k 在二进制下长得一样
因为 num % 2^i 相当于是把 num 除了 2^i, 这在位运算中是右移 i 位, 事实上这些被移走的二进制位就是余数
假如 num % 2^3 == 5, 而 5 在二进制下是 : 101
因此, 一个满足条件的 num 应该长这样:
    000 | 101   
    010 | 101
    011 | 101
    100 | 101
    101 | 101
    110 | 101
    111 | 101
    ...
    即 最后 i 位要等于 k
    我们现在的目的是要把这些数全部异或, 观察得, 这些数在 101 前面的二进制位对应上了从 0 开始的异或和
    我们把 x >> 3位, 再 << 3位, 然后再 + k, 如果原来的 x 小于现在的, 则为 x >> 3 - 1 个, 否则为 x >> 3 个
    现在给定区间[0, x], 我们要知道这个区间所有 B 类数 101 前面的异或和, 可以把 x 右移 3位, 然后套用 f(0, x >>= 3)
    接着我们要确认一共有多少个 101, 如果数量为偶数, 那么它们的异或和为 0, 否则为 k

*/