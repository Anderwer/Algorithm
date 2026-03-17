#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

int query(int l, int r)
{
    int res = 0;
    cout << "? " << l << " " << r << endl;
    cin >> res;
    return res;
}

void solve()
{
    int n;
    cin >> n;
    vector<int> ans(n + 1);
    int pos = 0;
    for(int i = 1; i < n; i++)
    {
        int cur = query(i, i + 1);
        if(cur == 1)
        {
            pos = i + 1;
            ans[i] = 0;
            ans[i + 1] = 1;
            break;
        }
    }

    if(pos == 0) cout << "! IMPOSSIBLE" << endl;
    else
    {
        int sum = query(1, pos);
        for(int i = 1; i <= sum; i++) ans[pos - i] = 0;
        for(int i = pos - sum - 1; i >= 1; i--) ans[i] = 1;
        for(int i = pos + 1; i <= n; i++)
        {
            int cur = query(1, i);
            if(cur > sum)
            {
                ans[i] = 1;
                sum = cur;
            }
            else ans[i] = 0;
        }
        cout << "! ";
        for(int i = 1; i <= n; i++) cout << ans[i];
        cout << endl;
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
1 0 0 0 1 1 0 1 0
先询问 [i, i + 1] 找到第一个 01 子序列的位置 p
然后询问 区间 [1, p] 得到的 01 子序列个数就是 p 前面有多少个 0, 把 0 从后往前放, 最前面放 1
然后从 p + 1 开始枚举查询 [1, i], 如果 sum 增加了 这个位置就是 1, 否则就是 0
*/