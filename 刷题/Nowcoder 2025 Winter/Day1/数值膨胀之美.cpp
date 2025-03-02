#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    vector<array<int, 2>> init(n + 1);
    multiset<int> st;
    for(int i = 1; i <= n; i++)
    {
        init[i] = {a[i], i};
        st.insert(a[i]);
    }
    sort(init.begin() + 1, init.end());
    st.erase(st.find(init[1][0]));
    st.insert(init[1][0] * 2);

    int ans = *st.rbegin() - *st.begin(); //情况 1
    int l = init[1][1], r = init[1][1]; //[l, r]为已经 x2 的区间
    for(int i = 2; i <= n; i++) //枚举次小值
    {
        int nxt = init[i][1];
        if(nxt >= l && nxt <= r) continue; //如果当前要修改的区间在[l, r]内则不修改
        for(int j = l - 1; j >= nxt; j--) //如果区间向左扩展
        {
            st.erase(st.find(a[j]));
            st.insert(a[j] * 2);
            ans = min(ans, *st.rbegin() - *st.begin());
        }
        for(int j = r + 1; j <= nxt; j++) //如果区间向右扩展
        {
            st.erase(st.find(a[j]));
            st.insert(a[j] * 2);
            ans = min(ans, *st.rbegin() - *st.begin());
        }
        l = min(l, nxt);
        r = max(r, nxt); //维护 x2 区间并集
    }
    cout << ans << "\n";
    
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
    return 0;
}

/*
对于ans = Max - Min, 要想让 ans 尽可能小, 就要让 Min 尽可能大, 因此让 Min x 2, 这样无非有两种情况
1. Min x 2 还是数组中的最小值
2. Min x 2 不是数组中的最小值

对于情况1. 答案就是 ans = Max - Min x 2
对于情况2. 此时的 Min x 2 不是最小值, 原本的次小值成为了现在的最小值 Min_now, 
先更新 ans = min(ans, Max - Min_now)
然后为了让 ans 又更小, 再把原本最小值到现在最小值之间的数全部 x 2, 这样能保证最小值不断增大
一直这样操作, 直到更新完所有次小值, 然后得到 ans 
*/