#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int N = 1e4 + 10;
int ans[N];

bool query(int x, int y)
{
    cout << "? " << x << " " << y << endl;
    int res;
    cin >> res;
    return res;
}
void print(int n)
{
    cout << "! ";
    for(int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << "\n";
}

void solve()
{
    int n, cnt = 1;
    cin >> n;
    n--;
    vector<int> now;
    for(int i = 1; i <= n; i++) ans[i] = 0;
    for(int i = 2; i <= n; i++)
    {
        if(query(1, i)) ans[i] = 0, cnt++;
        else
        {
            ans[i] = 1;
            now.push_back(i);
            break;
        }
    }
    
    for(int i = 2; i <= now[0] - 1; i++)
    {
        if(i + cnt <= n && query(i, i + cnt) == false)
        {
            ans[i + cnt] = i;
            now.push_back(i + cnt);
        }
        else cnt--;
    }

    while(cnt > 0)
    {
        vector<int> nxt;
        for(auto fa : now)
        {
            if(fa + cnt <= n && query(fa, fa + cnt) == false)
            {
                ans[fa + cnt] = fa;
                nxt.push_back(fa + cnt);
            }
            else cnt--;
        }
        now = nxt;
    }
    print(n);
}

int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(0), cout.tie(0);
    int t = 1;
    cin >> t;
    while(t--) solve();
    return 0;
}

/*
题中的树有一定的规则:
    节点1 的儿子只有一个, 假设是 节点x 
    节点1 ~ x - 1 都是和根节点相连
    节点1 ~ x - 1 的子树都是度为2的节点

先对 1 后面的节点提问, 如果 "? 1 x" 得到的 r = 0, 则 x 是 节点1 的儿子, 1 ~ x - 1 是 节点0 的儿子

此时已经确定了 1 ~ x 的具体位置, 接下来要确定 x + 1 ~ n 的位置

现在将 x + 1 ~ n 和 节点x 询问一次, 如果 "? x y" 得到的 r = 1, 那么 y 是 x 的儿子, 否则就停止, 因为如果当前的 y 不是, 那么 y+1 ~ y + 肯定也不是

然后再 对 节点2 ~ x - 1 执行以上操作

*/