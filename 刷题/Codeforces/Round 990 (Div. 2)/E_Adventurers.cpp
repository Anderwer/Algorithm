#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

template<typename T>
struct Fenwick
{
    int n;
    vector<T> a;

    Fenwick(int n_ = 0)
    {
        init(n_ + 3);
    }

    void init(int n_)
    {
        n = n_;
        a.assign(n, T{});
    }

    void add(int pos, const T& val)
    {
        for(int i = pos + 1; i < n; i += i & -i)
        {
            a[i] = a[i] + val;
        }
    }

    T internalQuery(int pos)
    {
        T res{};
        for(int i = pos + 1; i > 0; i -= i & -i)
        {
            res = res + a[i];
        }
        return res;
    }

    T get(int l, int r)
    {
        return internalQuery(r) - internalQuery(l - 1);
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<array<int, 2>> a(n);
    for(int i = 0; i < n; i++) cin >> a[i][0] >> a[i][1];
    
    set<int> xSet, ySet; //先用 set 给 x 和 y 去重
    for(auto [x, y] : a) xSet.insert(x), ySet.insert(y);

    map<int, int> yMap; //给 y 做离散化
    vector<int> yVector;
    int yNum = 0;
    for(auto y : ySet)
    {
        yVector.push_back(y);
        yMap[y] = yNum++;
    }
    for(int i = 0; i < n; i++) a[i][1] = yMap[a[i][1]]; //将离散化后的值标回
    sort(a.begin(), a.end()); //给 x 排序

    Fenwick<int> left_cnt(yNum + 2);
    Fenwick<int> right_cnt(yNum + 2);
    for(int i = 0; i < n; i++) right_cnt.add(a[i][1], 1); //一开始 x 在左边, 因此点全在 right_cnt

    int ans = 0;
    int xAns = 0, yAns = 0;
    int nowPos = 0;
    
    for(auto x : xSet) //从左到右枚举所有x
    {   
        while(nowPos < n && a[nowPos][0] < x)
        {
            left_cnt.add(a[nowPos][1], 1); //添加到左边
            right_cnt.add(a[nowPos][1], -1); //从右边删除
            nowPos++;
        }
        int l = 0, r = yNum;
        while(l <= r)
        {
            int mid = (l + r) / 2;
            int l1 = left_cnt.get(0, mid - 1);
            int l2 = left_cnt.get(mid, yNum);
            int r1 = right_cnt.get(0, mid - 1);
            int r2 = right_cnt.get(mid, yNum);
            int Min = min({l1, l2, r1, r2});
            if(Min > ans)
            {
                ans = Min;
                xAns = x;
                yAns = mid;
            }
            if(Min == l1 || Min == r1) l = mid + 1; //最小值在下方
            else r = mid - 1;  //最小值在上方
        }
    }
    cout << ans << "\n";
    cout << xAns << " " << yVector[yAns] << "\n";
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
题意: 有 n 个点, 你要选一个(x0, y0), 让他的坐标系把所有点分成四份, 要求最小的那份数量最大
首先贪心的想, 要选的点一定是 n 个点中的一个 x 值和一个 y 值(不一定要是一个点的x, y), 因为如果不选在这n个点上的x 或 y, 就算移动也不会对结果有影响

我们可以先枚举选点的 x, 现在问题是怎么快速在确定一个 x 的情况下得到 x 左边和右边的点的情况
我们可以先离散化所有的 y, 使得 y ∈ [0, n - 1], 然后用两个数组 left_cnt 和 right_cnt 从下往上给点的数量做前缀和
因此, 在确定一个 x 之后, 我们可以通过 left_cnt 和 right_cnt 对任意一个 y 的四个区域做出查询
举例, 确定了一个(x, y)后, 右上角点数为right_cnt[y - 1 ~ n], 右下角点数为right_cnt[0 ~ y - 1], 左上角点数为left_cnt[y - 1 ~ n], 左下角点数为left_cnt[0, y - 1]
此时的答案为 min(down, up), 如果下面小, 自然 y 就要往上移动, 因此可以对 y 进行二分

*/