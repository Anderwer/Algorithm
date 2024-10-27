#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 1e5 + 10;

pair<int, int> a[N];

bool cmp(pair<int, int>& a, pair<int, int>& b)
{
    return a.first + a.second < b.first + b.second;
}

void solve()
{
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        int x, y;
        cin >> x >> y;
        a[i] = make_pair(x, y);
    }
    sort(a + 1, a + 1 + n, cmp);
    for(int i = 1; i <= n; i++) cout << a[i].first << " " << a[i].second << " ";
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
假如有两对 <a[1], a[2]>, <b[1], b[2]>

在一对中, 不管怎么样都不会改变内部本身对逆序对数的贡献, 因此只需考虑外部

最优情况是 : a[1] < b[1] 且 a[1] < b[2] 
            a[2] < b[1] 且 a[2] < b[2]
不等式相加合并有 : a[1] + a[2] < b[1] + b[2]

因此, 贪心策略是对于每组的 sum 从小到大排序
*/