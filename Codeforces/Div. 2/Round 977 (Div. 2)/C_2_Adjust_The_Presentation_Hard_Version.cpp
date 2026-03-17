#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 2e5 + 10;

int a[N], b[N], inv[N];
int n, m, q;

void update(int x, int t, int& cnt, vector<int>& p, vector<set<int>>& f)
{
    if(inv[b[x]] - 1 > 0 && p[inv[b[x]] - 1] > p[inv[b[x]]]) cnt--;
    if(inv[b[x]] + 1 <= n && p[inv[b[x]]] > p[inv[b[x]] + 1]) cnt--;
    f[b[x]].erase(x);
    p[inv[b[x]]] = *f[b[x]].begin();
    if(inv[b[x]] - 1 > 0 && p[inv[b[x]] - 1] > p[inv[b[x]]]) cnt++;
    if(inv[b[x]] + 1 <= n && p[inv[b[x]]] > p[inv[b[x]] + 1]) cnt++;

    b[x] = t;
    if(inv[b[x]] - 1 > 0 && p[inv[b[x]] - 1] > p[inv[b[x]]]) cnt--;
    if(inv[b[x]] + 1 <= n && p[inv[b[x]]] > p[inv[b[x]] + 1]) cnt--;
    f[b[x]].insert(x);
    p[inv[b[x]]] = *f[b[x]].begin();
    if(inv[b[x]] - 1 > 0 && p[inv[b[x]] - 1] > p[inv[b[x]]]) cnt++;
    if(inv[b[x]] + 1 <= n && p[inv[b[x]]] > p[inv[b[x]] + 1]) cnt++;
}

void solve()
{
    cin >> n >> m >> q;
    for(int i = 1; i <= n; i++) cin >> a[i], inv[a[i]] = i;
    for(int i = 1; i <= m; i++) cin >> b[i];

    vector<set<int>> f(n + 1);
    vector<int> p(n + 1);
    for(int i = 1; i <= n; i++) f[i].insert(1e9);
    for(int i = 1; i <= m; i++) f[b[i]].insert(i);
    for(int i = 1; i <= n; i++) p[i] = *f[a[i]].begin();
    int cnt = 0;
    for(int i = 1; i < n; i++) if(p[i] > p[i + 1]) cnt++;
    if(cnt == 0) cout << "YA\n";
    else cout << "TIDAK\n";

    while(q--)
    {
        int x, t;
        cin >> x >> t;
        update(x, t, cnt, p, f);
        if(cnt == 0) cout << "YA\n";
        else cout << "TIDAK\n";
    }
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
分析得, 如果一个人已经讲过一次了, 那么他将能出现在任何位置, 无论之后轮到他讲多少次, 他都能被构造成立
如果 b 数组保持不变, 那么对于第 i 次演讲, 如果 b[i] == a[i] 那么可以将 b 中所有的 b[i] 去除, 同时 a[i] 也可以去掉
因此, 我们可以通过统计 b 数组中 第一次出现的人的序列, 如果能和 a 数组的前缀匹配上, 那么它就是好的

换个角度, 如果演讲是好的, 那么在 b 数组中必现出现 a[1], 再出现 a[2], 再出现 a[3], ...
此时我们可以用一个数组 p[i] 记录 a[i] 在 b 数组中第一次出现的位置
如果演讲是好的, 则满足 p[1] < p[2] < p[3] < ... < p[n]

如果 b 数组被修改, 将 b[x] 改为 t
则 人员t 在 b 数组的最早出现位置可能是 x 也可能不是
且 人员b[x] 将不在 x 位置出现
因此我们的数组 p[i] 需要持续修改,
如果还是保持原态, 则是好的

*/