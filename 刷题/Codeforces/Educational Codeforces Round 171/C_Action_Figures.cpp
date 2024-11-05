#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int N = 4e5 + 10;
char s[N];

void solve()
{
    int n;
    cin >> n;
    i64 ans = 0;
    for(int i = 1; i <= n; i++) cin >> s[i];
    queue<int> q;
    for(int i = n; i >= 1; i--)
    {
        if(s[i] == '1') q.push(i);
        else
        {
            if(!q.empty()) q.pop();
            ans += i;
        }
    }
    int num = q.size() / 2;
    while(num--) q.pop();
    while(!q.empty()) ans += q.front(), q.pop();
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
当遇到能买的时候, 我们可以选择当前这个数, 并且可以选择最左边没被买过的拼凑
我们可以从最右边遍历, 并且用一个队列维护 '1'的位置

如果遇到了 '1', 先压入队列中
如果遇到了 '0', 看队列中有没有 '1', 如果有, 则弹出一个'1', 并且加上当前这个 '0'

当所有 '0' 都与 '1' 匹配完了, 如果队列中还有 '1', 那么 要将 '1' 互相匹配, 则弹出 q.size() / 2, 剩下的都加到答案中
*/