#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<array<int, 2>> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i][0] >> a[i][1];

    vector<bool> skip(n + 1);
    vector<array<int, 5>> bL(n + 1);
    for(int i = 1; i <= n; i++) bL[i] = {a[i][0], -a[i][1], a[i][0], a[i][1], i}; //这样排序能按照L从小到大,R从大到小 bL[i][2]是L, bL[i][3]是R
    sort(bL.begin() + 1, bL.end());
    for(int i = 1; i < n; i++)
    {
        if(bL[i][2] == bL[i + 1][2] && bL[i][3] == bL[i + 1][3]) skip[bL[i][4]] = skip[bL[i + 1][4]] = true; //特判
    }
    vector<int> posR(n + 1, 0);
    set<int> setR;
    for(int i = 1; i <= n; i++)
    {
        if(skip[bL[i][4]] == true)
        {
            setR.insert(bL[i][3]);
            continue;
        }
        if(setR.lower_bound(bL[i][3]) == setR.end())
        {
            skip[bL[i][4]] = true;
            setR.insert(bL[i][3]);
        }
        else
        {
            int R = *(setR.lower_bound(bL[i][3]));
            posR[bL[i][4]] = R;
            setR.insert(bL[i][3]);
        }
    }

    vector<array<int, 5>> bR(n + 1);
    for(int i = 1; i <= n; i++) bR[i] = {-a[i][1], a[i][0], a[i][0], a[i][1], i}; //按照R从大到小, L从小到大
    sort(bR.begin() + 1, bR.end());
    vector<int> posL(n + 1, 0);
    set<int> setL;
    for(int i = 1; i <= n; i++)
    {
        if(skip[bR[i][4]] == true)
        {
            setL.insert(-bR[i][2]);
            continue;
        }
        if(setL.lower_bound(-bR[i][2]) == setL.end())
        {
            skip[bR[i][4]] = true;
            setL.insert(-bR[i][2]);
        }
        else
        {
            int L = *(setL.lower_bound(-bR[i][2]));
            posL[bR[i][4]] = -L;
            setL.insert(-bR[i][2]);
        }
    }

    for(int i = 1; i <= n; i++)
    {
        if(skip[i] == true) cout << 0 << "\n";
        else cout << posR[i] - a[i][1] + a[i][0] - posL[i] << "\n";
    }

/*
    for(int i = 1; i <= n; i++)
    {
        //cout << bL[i][2] << " " << bL[i][3] << "\n";
        //cout << bR[i][2] << " " << bR[i][3] << "\n";
        //cout << posR[i] << "\n";
        //cout << posL[i] << "\n";
    }
*/
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
题意: 有 n 条线段, 对第 i 条线段, 求所有包含第 i 条线段的线段集合的交集

先把所有线段按照 左端点L 从小到大排序, 相同的L 再按右端点R从大到小排序, 具体如下

---------------------------------------√
    --------------------------------------√
    ----------------------------------√
    -----------------------------√
    ----------------------
        ------------------------------√
        --------------------------√
       L---------------------R
        -----------------
            --------------------
            -----------------

假设当前正在查询 [L, R] 线段, 设这是从上往下数第 i 条线段, 这样排序的好处是只用考虑从 1 到 i 条线段, 下面的线段不用管
我们可以先把从第 1 条线段到第 i - 1 条线段的右端点R存到一个结构中并从小到大排好序, 
然后在查询第 i 条线段时先二分找第一个 >= R 的端点值, 这个就是交集的右端点
因此我们可以用一个 set 维护右端点R, 要找的时候二分即可, 一次性找完 n 条线段的并存在一个数组中

接下来更换排序方式, 将所有线段按照 右端点R从大到小排序, 相同的R 再按左端点从小到大排序(范围更大的始终在前)
然后从上到下二分找到第一个 <= L 的端点值(可以给所有L赋负值, 这样就能降序二分), 这个就是交集的左端点

对于排序后两个相邻的线段如果完全相同, 则这两条线段的答案均为 0 (此题特判)
*/