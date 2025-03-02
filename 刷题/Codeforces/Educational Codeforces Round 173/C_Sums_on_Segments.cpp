#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 2e5 + 10;
int a[N];
int n;

pair<int, int> get(int l, int r)
{
    int mx = 0, mn = 0;
    int mxx = 0, mnn = 1e9;
    for(int i = l; i <= r; i++)
    {
        mx = max(mx + a[i], a[i]);
        mxx = max(mxx, mx);
    }
    for(int i = l; i <= r; i++)
    {
        mn = min(mn + a[i], a[i]);
        mnn = min(mnn, mn);
    }
    return make_pair(mnn, mxx);
}

void solve()
{
    int pos = 0;
    cin >> n;
    for(int i = 1; i <= n; i++) 
    {
        cin >> a[i];
        if(a[i] != -1 && a[i] != 1) pos = i;
    }

    set<int> ans;
    ans.insert(0);
    auto res = get(1, pos - 1);
    for(int i = res.first; i <= res.second; i++) ans.insert(i); //[1, pos - 1]
    //cout << a_min << " " << a_max << "\n";

    res = get(pos + 1, n);
    for(int i = res.first; i <= res.second; i++) ans.insert(i); // [pos + 1, n]
    //cout << b_min << " " << b_max << "\n";

    int now = 0;
    for(int i = pos; i >= 1; i--)
    {
        now += a[i];
        ans.insert(now);
    }
    now = 0;
    for(int i = pos; i <= n; i++)
    {
        now += a[i];
        ans.insert(now);
    }

    int a_max = 0, a_min = 0, b_max = 0, b_min = 0;
    int a_now = 0, b_now = 0;
    for(int i = pos - 1; i >= 1; i--)
    {
        a_now += a[i];
        a_max = max(a_max, a_now);
        a_min = min(a_min, a_now);
    }
    for(int i = pos + 1; i <= n; i++)
    {
        b_now += a[i];
        b_max = max(b_max, b_now);
        b_min = min(b_min, b_now);
    }
    for(int i = a_min + b_min + a[pos]; i <= a_max + b_max + a[pos]; i++) ans.insert(i);

    cout << ans.size() << "\n";
    for(auto p : ans) cout << p << " ";
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
思路：
先不考虑x, 将数组分为 [A] [x] [B], 则[A] 和 [B] 都是只含 -1 和 1的
求[A] 和 [B]的子区间取值情况, 可以先求出子区间最大值和子区间最小值, 显然子区间的取值是[min, max]
求最大和最小可以线性DP
*/