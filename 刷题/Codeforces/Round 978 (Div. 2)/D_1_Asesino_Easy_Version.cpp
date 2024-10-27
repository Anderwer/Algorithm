#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

int query(int x, int y)
{
    int res;
    cout << "? " << x << " " << y << endl;
    cin >> res;
    return res;
}

void solve()
{
    int n;
    cin >> n;
    int pos = -1;
    for(int i = 1; i < n; i += 2)
    {
        int res1 = query(i, i + 1);
        int res2 = query(i + 1, i);
        if(res1 != res2)
        {
            pos = i;
            break;
        }
    }
    if(pos == -1) cout << "! " << n << endl;
    else if(pos == 1)
    {
        if(query(pos + 1, pos + 2) == query(pos + 2, pos + 1)) cout << "! " << pos << endl;
        else cout << "! " << pos + 1 << endl;
    }
    else if(pos == n - 1)
    {
        if(query(pos, pos - 1) == query(pos - 1, pos)) cout << "! " << pos + 1 << endl;
        else cout << "! " << pos << endl;
    }
    else
    {
        if(query(pos + 1, pos + 2) == query(pos + 2, pos + 1)) cout << "! " << pos << endl;
        else cout << "! " << pos + 1 << endl;
    }
}
int main()
{
    //std::ios::sync_with_stdio(false);
    //std::cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}

/*
观察得, 当询问了一组 <i, j> , 如果 i 认为 j 的身份和 j 认为 i 的身份不一致, 则 <i, j> 中必有内鬼

可以把 n 个人分成 <1, 2>, <3, 4>, ..., <i, i + 1>, <i + 2, i + 3> 组
在每一组中两个人互相问, 最终找到答案不同的一组, 则确定了内鬼在这一组中
假设是 <k, k + 1> 组
再对 <k - 1, k> 和 <k + 1, k + 2> 问一下就能得出谁是内鬼

<1, 2> <3, 4> <5, 6>
*/