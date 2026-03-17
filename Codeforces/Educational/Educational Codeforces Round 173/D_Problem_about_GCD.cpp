#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    i64 l, r, g;
    cin >> l >> r >> g;
    i64 L = (l - 1) / g + 1;
    i64 R = r / g;

    for(i64 len = R - L; len >= 0; len--)
    {
        for(i64 x = L; x + len <= R; x++)
        {
            if(gcd(x, x + len) == 1)
            {
                cout << x * g << " " << (x + len) * g << '\n';
                return;
            }
        }
    }
    cout << "-1 -1\n";
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
思路：
让 A = k * g, B = x * g
则要使gcd(A, B) = g, 则有gcd(k, x) = 1
又因为 k ∈ [l / g, r / g], x ∈ [l / g, r / g]
则将问题转化为在区间 [l / g, r / g] 内找最远互质点对

首先我们枚举一下区间长度len, 从 R - L 到 R - L - 60 从大到小枚举
然后枚举点对的左点 x , 则右点为 x + len
第一个找到符合的点对即为最优解

*/