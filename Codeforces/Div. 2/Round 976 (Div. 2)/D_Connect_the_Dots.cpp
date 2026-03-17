#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 2e5 + 10;

int fa[N];

int find(int x)
{
    if(x == fa[x]) return x;
    return fa[x] = find(fa[x]);
}

void unionn(int x, int y)
{
    int fa_x = find(x);
    int fa_y = find(y);
    if(fa_x == fa_y) return;
    fa[fa_x] = fa_y;
}

void solve()
{
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++) fa[i] = i;

    vector<pair<int, int>> point[11][11];
    for(int i = 1; i <= m; i++)
    {
        int a, d, k;
        cin >> a >> d >> k;
        point[d][a % d].push_back({a, a + k * d});
    }

    for(int i = 1; i <= 10; i++) //枚举 d
    {
        for(int j = 0; j < i; j++) //枚举 a % d
        {
            sort(point[i][j].begin(), point[i][j].end()); // 按左端点排序
            int len = point[i][j].size();
            int L = 0, next_L = 0;
            while(L < len) //枚举每一个左端点
            {
                int pos_l = point[i][j][L].first;
                int pos_r = point[i][j][L].second;
                while(next_L < len && point[i][j][next_L].first <= pos_r) //提前找到下一个L的位置, 减少遍历时间
                {
                    pos_r = max(pos_r, point[i][j][next_L].second);
                    next_L++;
                }
                for(int p = pos_l; p < pos_r; p += i) unionn(p, p + i); //把每个点都加进并查集
                L = next_L;
            }
        }
    }
    int ans = 0;
    for(int i = 1; i <= n; i++)
    {
        if(find(i) == i) ans++;
    }
    cout << ans << "\n";
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
由于d <= 10, 显然从 d 下手
注意到, 在相同的 d 下, 有不同的a[i]
对每一个a[i]有, a[i], a[i] + d, a[i] + 2d, ..., a[i] + kd 模 d 的值相同
因此我们可以用一个数组point[d][a % d] 归类一些点, 这些点连边后属于同一个联通块
之后对每一类的联通块进行并查集合并即可
而point[][] 一共有 point[1 ~ 10][0 ~ d - 1] 种类型, 100种
O(n + d^2)
*/