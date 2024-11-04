#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

void solve()
{
    int n, k;
    cin >> n >> k;
    if(n == 1)
    {
        cout << 1 << "\n";
        cout << 1 << "\n";
        return;
    }
    vector<int> ans;
    if(k & 1)
    {
        if(k == 1 || k == n)
        {
            cout << -1 << "\n";
            return;
        }
        ans.push_back(1);
        ans.push_back(2);
        ans.push_back(k);
        ans.push_back(k + 1);
        ans.push_back(k + 2);
    }
    else
    {
        ans.push_back(1);
        ans.push_back(k);
        ans.push_back(k + 1);
    }
    cout << ans.size() << "\n";
    for(auto v : ans) cout << v << " ";
    cout << "\n";
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
子数组的长度也要是 len = odd
一共有 m 个子数组, m也要是 odd

len * m = n

k 的位置可以在 a 中得到
如果 k 是偶数, 则 k 左边和右边都是奇数
如果 k 是奇数, 则 k 左边和右边都是偶数
假设左边数量为 left, 右边数量为 right
要满足左边分的组数 = 右边分的组数
如果 左边和右边都是奇数, 则左右都分一组, m = 3
如果 左边和右边都是偶数, 则左右都分两组, m = 5
对于分两组, {1}, {2 ~ left}, {k}, {k + 1}, {k + 2, n}

*/