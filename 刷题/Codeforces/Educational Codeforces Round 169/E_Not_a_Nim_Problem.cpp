#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 3e5 + 10;
const int M = 1e7 + 10;
int a[N], sg[M];
bitset<M> vis;

void init()
{
    for(int i = 0; i < M; i++) sg[i] = 1e9;
    for(int i = 2; i < M; i += 2) sg[i] = 0;
    sg[1] = 1;
    vis.set();
    int now = 0;
    for(int i = 2; i < M; i++)
    {
        if(vis[i])
        {
            sg[i] = ++now;
            for(int j = i << 1; j < M; j += i)
            {
                vis[j] = 0;
                sg[j] = min(sg[j], now);
            }
        }
    }
    sg[2] = 0;
}

void solve()
{
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    int res = 0;
    for(int i = 1; i <= n; i++) res ^= sg[a[i]];
    if(res) cout << "Alice\n";
    else cout << "Bob\n";
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    init();
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}

/*
SG 函数打表
根据打表发现: sg[x]的取值有规律
当 sg[x] = 0 时, x 为偶数
当 sg[x] = 1 时, x = 1
当 sg[x] = 2 时, x 为 以第二个质数作为质因子的所有未被选过的数
当 sg[x] = 3 时, x 为 以第三个质数作为质因子的所有未被选过的数
...

因此, 可以用质数筛标记一下
*/