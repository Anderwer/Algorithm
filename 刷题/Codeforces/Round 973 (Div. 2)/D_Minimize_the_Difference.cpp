#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 2e5 + 10;
i64 a[N];
int n;

bool check_min(i64 x) //检查是否满足最小值
{
    i64 sum = 0;
    for(int i = 1; i <= n; i++) //如果有比最小值大的数, 记在sum里分给后面比最小值小的数, 如果不够分了则 false
    {
        if(a[i] > x) sum += a[i] - x;
        if(a[i] < x) sum -= x - a[i];
        if(sum < 0) return false; //不够分了, 不满足
    }
    return true;
}

bool check_max(i64 x) //检查是否满足最大值
{
    i64 sum = 0;
    for(int i = 1; i <= n; i++)
    {
        if(a[i] > x) sum += a[i] - x; //如果有比最大值还大的数, 它应该分给更小的数
        if(a[i] < x) sum -= x - a[i], sum = max(sum, 0LL); // sum如果小于0, 那么就是不够分给比它小的, 但是这不影响最大值, 因此重置 sum = 0 即可
    }
    if(sum > 0) return false; //还有多的数没分完, 说明答案太小了
    else return true;
}
void solve()
{
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];

    i64 L = 0, R = 1e12, ans_min = 0;
    while(L <= R)
    {
       i64 mid = (L + R) / 2;
       if(check_min(mid)) ans_min = mid, L = mid + 1;
       else R = mid - 1; 
    }

    L = 0, R = 1e12;
    i64 ans_max = 0;
    while(L <= R)
    {
        i64 mid = (L + R) / 2;
        if(check_max(mid)) ans_max = mid, R = mid - 1;
        else L = mid + 1;
    }

    cout << ans_max - ans_min << "\n";
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
如果一个数的右边存在比它小的数, 则他俩可以平均
因此最后平均的结果是 a 数组变成了非单调递减的数组

而一个数组具有单调性, 我们就可以二分答案找最小值里的最大和最大值里的最小

*/