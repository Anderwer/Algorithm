#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    unordered_map<int, int> cnt;
    unordered_map<int, int> vis;
    
    i64 suf = 0; 
    for(int i = 1; i <= n; i++)
    {
        if(cnt[a[i]] == 0) suf++;
        cnt[a[i]]++;
    }
    
    i64 ans = 0;
    queue<int> q;
    for(int i = 1; i <= n; i++) //枚举第二个 p
    {
        cnt[a[i]]--;
        if(cnt[a[i]] == 0) suf--;
        if(a[i] == 0)
        {
            while(!q.empty())
            {
                vis[q.front()] = 2;
                q.pop();
            }
            continue;
        }
        if(!vis[a[i]]) //去重, 防止标记过多
        {
            vis[a[i]] = 1;
            q.push(a[i]);
        }
        else if(vis[a[i]] == 2) // vis[a[i]] == 1 表示 a[i] 出现过, vis[a[i]] == 2 表示 a[i] 出现过且当前位置前面存在 a[i]
        {
            ans += suf;
            if(cnt[0] > 0) ans--;
            vis[a[i]] = 3; //随便标记一个非 0, 1, 2 的
        }
    }
    cout << ans << "\n";
}

// 只要遇到 0, 就把 0 前面的数全标记起来
// 可以用一个队列, 先把数全部存进去, 遇到 0 的时候再全部弹出标记一下
// 如果遇到了被标记过的 a[i], 则统计 a[i] 后面的所有数的种类 suf
// 可以用 cnt 先预处理一下得到 suf,再持续更新 suf
// ans += suf
// 注意如果 suf 中统计了数字 0, 要 ans -= 1, 因为限制 p, q 是正整数

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
