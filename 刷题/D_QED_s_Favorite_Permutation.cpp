#include <bits/stdc++.h>
#define lc k << 1
#define rc k << 1 | 1

using i64 = long long;
using namespace std;
const int N = 2e5 + 10;
int a[N];
char s[N];
bool mark[N], vis[N];

void solve()
{
    int n, q;
    cin >> n >> q;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) cin >> s[i];
    for(int i = 1; i <= n; i++) mark[i] = vis[i] = false;

    int mx = 0, cnt = 0;
    for(int i = 1; i <= n; i++)
    {
        mx = max(mx, a[i]);
        if(mx > i) mark[i] = true;    
    }
    for(int i = 1; i < n; i++)
    {
        if(s[i] == 'L' && s[i + 1] == 'R' && mark[i] == true)
        {
            cnt++;
            vis[i] = true;
        }
    }

    while(q--)
    {
        int pos; cin >> pos;
        if(s[pos] == 'L')
        {
            s[pos] = 'R';
            if(s[pos + 1] == 'R' && vis[pos] == true) vis[pos] = false, cnt--;
            if(s[pos - 1] == 'L' && vis[pos - 1] == false && mark[pos - 1] == true) vis[pos - 1] = true, cnt++;
        }
        else
        {
            s[pos] = 'L';
            if(s[pos + 1] == 'R' && vis[pos] == false && mark[pos] == true) vis[pos] = true, cnt++;
            if(s[pos - 1] == 'L' && vis[pos - 1] == true) vis[pos - 1] = false, cnt--;
        }
        if(cnt == 0) cout << "YES\n";
        else cout << "NO\n";
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
要使 a 数组排成升序, 且 a 是排列, 则最终应该都是 a[i] = i
观察得, 对于任意一个区间, 对应的s串只有4种形式:
...LLL...
...RRR...
...RL...
...LR...
显然前三种都可以把一个数交换到任意地方, 只有第4种不行
当碰到第四种情况时, 假设 ...LR... 中的 L 的下标是 i
由于是排列, 每个数具有唯一性, 能够排序的条件为以下两条:
     对于 i 左边的数, 全部满足 a[左] < i
     对于 i + 1 右边的数, 全部满足 a[右] > i + 1
假设有一个 s 中有 k 组形如 "...LR..." 的子串, 如果对每个组都判断一次, 显然超时
我们可以先对每一个数判断它的左边是否有比它下标大的数, 如果有则 mark[i] = true
然后再用一个 cnt 记录一下 这 k 组子串有多少组不符合排序条件, 当 s[i] == 'L' && s[i + 1] == 'R' && mark[i] == true 时不符合条件
对不符合条件的组我们也标记一下 vis[i] = true

每次询问要做一次修改, 这时候我们修改 s[i] 和 vis[i] 和 cnt即可
如果 cnt = 0, 则没有冲突, 可以排序
*/