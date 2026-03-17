#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    i64 x, m;
    cin >> x >> m;

    i64 ans = m / x; //处理 (x ⨁ y) | x
    i64 k = m / x;
    if(((k * x) ^ x) >= 1 && ((k * x) ^ x) <= m) ans++;
    if((((k + 1) * x) ^ x) >= 1 && (((k + 1) * x) ^ x) <= m) ans++;
    if(k - 1 >= 1) ans--; //排除 k = 1 的情况

    for(i64 y = 1; y <= min(x - 1, m); y++)
    {
        if((x ^ y) % y == 0) ans++;
    }
    cout << ans << "\n";
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

/*
求解 (x ⨁ y) | x 或 (x ⨁ y) | y 的情况, 可以分类讨论

对于 (x ⨁ y) | x
引理 : (x ⨁ y) ∈ [|x - y|, x + y]
由于 (x ⨁ y) | x, 则设 (x ⨁ y) = kx, 移项得 y = (kx ⨁ x)
由引理得, y ∈ [(k - 1) * x, (k + 1) * x]
又因为 y <= m, 则有 (k + 1) * x <= m, 得 k <= [m / x] - 1(下取整)
设 j = [m / k](下取整)
因此 k ∈ [0, j - 1], 但要特判 k = 1 时 有 (x ⨁ y) = x, 此时 y = 0 不符合题意
但是当 k = j 或 k = j + 1 时, 带入 y = (kx ⨁ x) 发现, 此时的 y 可能符合 y <= m 的条件, 要特判

对于 (x ⨁ y) | y
    当 y < x 时, 枚举 y ∈ [1, x) 统计答案

    当 y >= x 时, (x ⨁ y) ∈ [y - x, x + y]
    设 (x ⨁ y) = ky, 则有 ky <= x + y
    当 k = 0 时, 有 x = y, 与第一种情况的 k = 0 时重复
    当 k = 1 时, 有 x = 0, 不符合题意
    当 k = 2 时, 有 y <= x, 又因为 y >= x, 所以 y = x, 重复
    当 k > 2 时, 有 y <= x / (k - 1), 与 y >= x 矛盾

因此, 对于 (x ⨁ y) | y 的情况只用处理 y < x 的枚举
*/