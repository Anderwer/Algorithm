#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<int> p_q(n + 1), p_k(n + 1), p_j(n + 1);
    for(int i = 1; i <= n; i++) cin >> p_q[i];
    for(int i = 1; i <= n; i++) cin >> p_k[i];
    for(int i = 1; i <= n; i++) cin >> p_j[i];

    vector<bool> f(n + 1, false);
    vector<array<int, 2>> path(n + 1);
    vector<array<int, 2>> Max(3); //Max[0][0] : Q排列的 max    Max[0][1]: Q排列的max的位置
    f[1] = true;
    Max[0][0] = p_q[1];
    Max[1][0] = p_k[1];
    Max[2][0] = p_j[1];
    Max[0][1] = Max[1][1] = Max[2][1] = 1;
    for(int i = 2; i <= n; i++)
    {
        if(Max[0][0] > p_q[i]) {f[i] = true; path[i] = {'q', Max[0][1]};}
        if(Max[1][0] > p_k[i]) {f[i] = true; path[i] = {'k', Max[1][1]};}
        if(Max[2][0] > p_j[i]) {f[i] = true; path[i] = {'j', Max[2][1]};}
        if(f[i] == false) continue;
        if(p_q[i] > Max[0][0]) Max[0][0] = p_q[i], Max[0][1] = i;
        if(p_k[i] > Max[1][0]) Max[1][0] = p_k[i], Max[1][1] = i;
        if(p_j[i] > Max[2][0]) Max[2][0] = p_j[i], Max[2][1] = i;
    }
    if(f[n] == true)
    {
        cout << "YES\n";
        vector<array<int, 2>> ans;
        for(int i = n; i > 1; i = path[i][1]) ans.push_back({path[i][0], i});
        cout << ans.size() << "\n";
        for(int i = ans.size() - 1; i >= 0; i--) cout << (char)ans[i][0] << " " << ans[i][1] << '\n';
    }
    else cout << "NO\n";
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
题意转化: 现在有三个人, 每个人都有一个排列 p, 当位于位置 i 时, 如果有 j < i 且 p[j] > p[i], 则连有一条 j -> i 的有向边
现在你从 1 出发, 问是否能走到 n, 如果能的话输出每一步是选的哪个人的排列且输出到达的点是哪个点
其中, 只要存在点 j -> i的边, 可以从三个人中任选一人

现在设 f[i] : 是否能走到位置 i, f[i] = true 表示能走到 i
转移 : 当转移 f[i] 时, 在所有 j < i 且 f[j] = true 的点中找是否存在 p[j] > p[i], 如果存在则 f[i] 可以走到
但是这样的转移是 O(n2) 的, 考虑优化. 我们可以维护一个 max{p[j]}, 其中 j < i 且 f[j] = true, 然后每次转移的时候让 max 和 p[i] 比较即可

现在考虑记录路径, 我们可以在维护 max{p[j]} 的时候顺便把 位置 j 和 现在正在哪个人的排列 塞进去
如果当前有 max{p[j]} > p[i], 则 path[i] = {j, name}
*/