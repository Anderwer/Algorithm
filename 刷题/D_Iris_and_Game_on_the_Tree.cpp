#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int N = 2e5 + 10;
char s[N];
int d[N];

void solve()
{
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) d[i] = 0; //统计每个点的度数, 度为 1 且 i != 1 的为叶子节点
    for(int i = 1; i <= n - 1; i++)
    {
        int u, v; cin >> u >> v;
        d[u]++, d[v]++;
    }
    for(int i = 1; i <= n; i++) cin >> s[i];

    int cnt_0 = 0, cnt_1 = 0, cnt_x = 0, cnt_f = 0;
    for(int i = 2; i <= n; i++)
    {
        if(d[i] == 1) //叶子节点
        {
            if(s[i] == '0') cnt_0++;
            else if(s[i] == '1') cnt_1++;
            else cnt_x++;
        }
        else
        {
            if(s[i] == '?') cnt_f++;
        }
    }
    int ans = 0;
    if(s[1] == '?')
    {
        if(cnt_0 == cnt_1)
        {
            if(cnt_f & 1) ans = cnt_0 + (cnt_x + 1) / 2;
            else ans = cnt_0 + cnt_x / 2;
        }
        else ans = max(cnt_0, cnt_1)+ cnt_x / 2;
    }
    else
    {
        if(s[1] == '1') ans = cnt_0 + (cnt_x + 1) / 2;
        else ans = cnt_1 + (cnt_x + 1) / 2;
    }
    cout << ans << "\n";
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
这题有个关键性质
注意到: 01字符串 当且仅当字符串首尾相等时 "10" 和 "01" 子串数量的差值才为0, 否则为 1
因为如果字符串中存在某些连续的 '1' 或者连续的 '0', 我们可以把它们删去, 化简成 "101010...1" 和 "101010...0" 两种形式, 前者差值一直为 0, 后者差值一直为 1

如果根节点的值确定了:
    我们可以统计叶子节点 '0' 和 '1' 还有 '?' 的数量 cnt_0, cnt_1, cnt_x
    如果根节点为 '1':
        在未确定所有 '?' 时, 树的得分为 cnt_0, iris先手且想让得分最大化, 则 iris 会尽可能把 '?' 变成 '0', 至多 (cnt_x + 1) / 2 个
        因此 ans = cnt_0 + (cnt_x + 1) / 2

    如果根节点为 '0':
        情况类似, ans = cnt_1 + (cnt_x + 1) / 2

如果根节点的值没确定:
    我们可以统计叶子节点 '0' 和 '1' 还有 '?' 的数量 cnt_0, cnt_1, cnt_x
    如果 cnt_0 != cnt_1:
        此时 iris  先选根节点, 如果 '1' 多, 则根节点选 '0', 之后 iris 还可以在叶子节点中选 cnt_x / 2 个 '1', ans = max(cnt_0, cnt_1) + cnt_x / 2
    如果 cnt_0 == cnt_1:
        由于 iris 是先手, 如果 iris 先不抢根节点, 而 dora 第二手选择了根节点, 那么 iris 可以多选一个叶子节点, 但主动权在 dora 手上, 不能最优, ans = cnt_0 + cnt_x / 2
        如果 iris 先手选择了根节点, 则 dora 可以多选一个叶子节点, 依然不能最优, ans = cnt_0 + cnt_x / 2
        因此, 谁先对根节点和叶子节点动手, 则谁更亏

        考虑非根非叶子节点上 '?' 的数量: cnt_f
        如果 cnt_f 是奇数, 则可以先后手置换, 让 iris 变成后手, ans = cnt_0 + (cnt_x + 1) / 2
        如果 cnt_f 是偶数, 则 iris 只能更亏, ans = cnt_0 + cnt_x / 2
*/