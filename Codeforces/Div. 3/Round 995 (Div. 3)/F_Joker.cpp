#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> a(q + 1);
    for(int i = 1; i <= q; i++) cin >> a[i];

    vector<array<int, 2>> range; //range[i][0] 第i个区间左端点, range[i][1] 第i个区间右端点
    range.push_back({m, m}); 
    bool has_head_tail = false;
    for(int i = 1; i <= q; i++)
    {
        bool flag = false;
        for(int j = range.size() - 1; j >= 0; j--) //range[j] 第 j 个区间, range[0] 是原始区间
        {
            if(a[i] >= range[j][0] && a[i] <= range[j][1])
            {
                if(a[i] == range[j][0] && a[i] == range[j][1] && range[j][0] != 1 && range[j][1] != n) 
                {
                    range.erase(range.begin() + i); //删区间
                }
                flag = true; // 标记一下 当前的 a[i] 是否存在一个区间内
            }
            else if(a[i] < range[j][0]) range[j][0]--;
            else if(a[i] > range[j][1]) range[j][1]++;
        }

        if(flag == true && has_head_tail == false) //处理头尾
        {
            has_head_tail = true;
            bool has_head = false, has_tail = false;
            for(int k = 0; k < range.size(); k++)
            {
                if(range[k][0] <= 1 && range[k][1] >= 1) has_head = true;
                if(range[k][0] <= n && range[k][1] >= n) has_tail = true;
            }
            if(has_head == false) range.push_back({1, 1});
            if(has_tail == false) range.push_back({n, n});
        }

        sort(range.begin(), range.end());
        int last = 0;
        i64 res = 0;
        for(int j = 0; j < range.size(); j++)
        {
            int left = max(range[j][0], last);
            int right = range[j][1];
            res += (right - left + 1);
            last = right + 1;
        }
        cout << res << " ";
    }
    cout << "\n";
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
注意到, 如果要移动的牌在 Joker 左边, 那么 Joker牌的位置集合向左扩展 +1
如果在右边, 那么 Joker牌的位置集合向右扩展 +1

如果要移动的牌刚好是 Joker所在位置, 那么 集合增加 {1, n} 两个点

如果要移动的牌在 Joker牌位置集合内, 易证不会改变Joker牌位置集合

我们将集合视为区间
首先在刚开始, 我们加入一个区间[m, m]
然后根据上面的分析进行区间扩散, 可以变为 [m - 1, m] 或是 [m, m + 1] 或是分解成 [1, 1] 和 [n, n] (当a[i] == m 时)
如果有分解过的话我们就 flag 标记为 true
*/