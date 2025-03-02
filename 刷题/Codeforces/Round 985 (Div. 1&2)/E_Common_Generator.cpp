#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 1e6 + 10;
bitset<N> vis;
vector<int> pri;

void prime()
{
    vis.set();
    vis[0] = vis[1] = 0;
    for(int i = 2; i * i < N; i++) if(vis[i]) for(int j = i << 1; j < N; j += i) vis[j] = 0;
    for(int i = 2; i < N; i++) if(vis[i]) pri.push_back(i);
}

void solve()
{
    int n;
    cin >> n;
    vector<i64> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    int primeCnt = 0;
    for(int i = 1; i <= n; i++)
    {
        if(vis[a[i]] == true) primeCnt++; 
    }

    if(primeCnt >= 2)
    {
        cout << -1 << "\n";
        return;
    }
    if(primeCnt == 0) cout << 2 << "\n";
    else
    {
        i64 ans = 0;
        for(int i = 1; i <= n; i++)
        {
            if(vis[a[i]]) ans = a[i];
        }
        for(int i = 1; i <= n; i++)
        {
            if(a[i] == ans) continue;
            if(a[i] < ans * 2)
            {
                cout << -1 << "\n";
                return;
            }
            if(a[i] % 2 == 0) continue;
            else // a[i] is odd
            {
                int minP = 0;
                for(auto v : pri)
                {
                    if(a[i] % v == 0)
                    {
                        minP = v;
                        break;
                    }
                }
                if(a[i] - minP < ans * 2)
                {
                    cout << -1 << "\n";
                    return;
                }
            }
        }
        cout << ans << "\n";
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    cin >> t;
    prime();
    while(t--){
        solve();
    }
    return 0;
}

/*                     d
考虑把 x 变成 y 时, x -----> y
设 y = x + d, 而 d 是 x 的约数, 再设 x = d * k
则有 y = d * k + d = d * (k + 1)
分析 y = d * (k + 1), 形式上 y 是一个合数

1#. 如果 y 是一个合数, 当 y 是偶数时, 可以由 x0 = 2 一直 加2 得到
    当 y 是奇数时, 又因为 y = d * (k + 1), 则 d 是奇数且 k 是偶数, 而 x = d * k, 所以 x 是偶数, 可以由 x0 = 2 一直加到 x
    然后再取 x 的约数 d, 这样即可加到 y
    因此, 如果 a[] 中无质数, x = 2 可以构造所有的 a[i]

2#. 如果 y 是一个质数, 当且仅当 x == y 时才成立, 显然, 如果 a[] 中质数个数 >= 2 则不可能

3#. 如果 y 是一个质数 p , 且 a[] 中只有一个质数, 则此时 x = y = p, 此时 x 的变化路线为:
    p ----> 2p ----> 2p + 2 ----> 2p + 4 ----> ....even ----> ....
    根据上述变化, 对于一个数 a[i], 考虑几种情况:
    (1). 如果 a[i] < 2p 且 a[i] != p, 则无法构造
    (2). 如果 p | a[i], 则 可以构造
    (3). 如果 a[i] 是偶数, 因为 a[i] >= 2p, 而之后可以一直选择 d = 2, 因此可以构造
    (4). 如果 a[i] 是奇数, 由于 a[i] 是合数, 设 a[i] = t * q, 则 t, q 都为奇数
         a[i] = t * q = t * (q - 1) + t, 前面的 t * (q - 1) 是偶数, 只需要判断是否存在一个 t 使得 t * (q - 1) >= 2p
         而所有合法的 t 即为 a[i] 的质因数, 判断最小质因数即可
*/