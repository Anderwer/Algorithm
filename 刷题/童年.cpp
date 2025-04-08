#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

map<array<int, 5>, int> vis;
int dfs(array<int, 5> s) // vis[s] = 1 表示状态 s 玩家 A 必胜
{
    if(vis[s]) return vis[s];
    if(s[0] == s[1] == 0) return vis[s] = 1;
    if(s[2] == s[3] == 0) return vis[s] = 2;

    set<int> st;
    if(s[4] == 1) // 当前为 A 操作
    {
        st.insert(dfs({(s[0] + s[2]) % 10, s[1], s[2], s[3], s[4] ^ 1})); // Ax + Bx
        st.insert(dfs({(s[0] + s[3]) % 10, s[1], s[2], s[3], s[4] ^ 1})); // Ax + By
        st.insert(dfs({s[0], (s[1] + s[2]) % 10, s[2], s[3], s[4] ^ 1})); // Ay + Bx
        st.insert(dfs({s[0], (s[1] + s[3]) % 10, s[2], s[3], s[4] ^ 1})); // Ay + By
    }
    else
    {
        st.insert(dfs({s[0], s[1], (s[2] + s[0]) % 10, s[3], s[4] ^ 1}));
        st.insert(dfs({s[0], s[1], (s[2] + s[1]) % 10, s[3], s[4] ^ 1}));
        st.insert(dfs({s[0], s[1], s[2], (s[3] + s[0]) % 10, s[4] ^ 1}));
        st.insert(dfs({s[0], s[1], s[2], (s[3] + s[1]) % 10, s[4] ^ 1}));
    }
    for(int i = 1; ; i++)
        if(!st.count(i)) return vis[s] = i;
}

void solve()
{
    array<int, 5> s; // {Ax, Ay, Bx, By, id} id 为 1 表示当前 A 操作
    cin >> s[0] >> s[1] >> s[2] >> s[3];
    s[4] = 1;

    int ans = dfs(s);
    cout << ans << '\n';
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--)
    {
        solve();
    }
    return 0;
}
