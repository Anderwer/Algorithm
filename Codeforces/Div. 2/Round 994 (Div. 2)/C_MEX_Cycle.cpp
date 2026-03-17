#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n, x, y;
    cin >> n >> x >> y;
    vector<int> a(n + 1, 0);

    if(x + 1 == y)
    {
        if(n & 1)
        {
            for(int i = 1; i < n; i += 2) a[i] = 1;
            a[n] = 2;
        }
        else
        {
            for(int i = 1; i <= n; i += 2) a[i] = 1;
        }
    }
    else 
    {
        int part1 = y - x - 1;
        int part2 = n - y + x - 1;
        if(part1 % 2 == 0 && part2 % 2 == 0)
        {
            for(int i = 1; i <= n; i += 2) a[i] = 1;
        }
        else if(part1 % 2 == 1 && part2 % 2 == 1)
        {
            int pos1 = (x + y) / 2;
            int pos2 = ((y + x + n) / 2) % n;
            if(pos2 == 0) pos2 = n;
            a[pos1] = a[pos2] = 2;
            int xx = 1, yy = 0;
            
            for(int i = 1; i < abs(pos1 - pos2); i++)
            {
                int nxt1 = min(pos1, pos2) + i;
                int nxt2 = min(pos1, pos2) - i;
                if(nxt1 > n) nxt1 = nxt1 % n;
                if(nxt2 < 0) nxt2 = (nxt2 + n) % n;
                if(nxt2 == 0) nxt2 = n;
                a[nxt1] = xx;
                a[nxt2] = yy;
                swap(xx, yy);
            }
        }
        else
        {
            if(part1 % 2 == 1)
            {
                int pos = (x + y) / 2;
                if(pos == 0) pos = n;
                a[pos] = 2;
                int xx = 0;
                for(int i = 1; i <= n; i++)
                {
                    if(i == pos) continue;
                    a[i] = xx;
                    xx ^= 1;
                }
            }
            else if(part2 % 2 == 1)
            {
                int pos = ((y + x + n) / 2) % n;
                if(pos == 0) pos = n;
                a[pos] = 2;
                int xx = 0;
                for(int i = 1; i <= n; i++)
                {
                    if(i == pos) continue;
                    a[i] = xx;
                    xx ^= 1;
                }
            }
        }
    }
    for(int i = 1; i <= n; i++) cout << a[i] << " ";
    cout << "\n";
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
先考虑 x + 1 == y 的情况, 此时的朋友关系相当于没变
1#. 如果 n 是偶数, 则可以是 "1 0 1 0 1 0" 的形式(画图)
2#. 如果 n 是奇数, 则可以是 "1 0 1 0 ... 2" 的形式

再考虑 x + 1 != y 的情况, 此时相当于 x 和 y多连了一条边
先将 a[x] 和 a[y] 设为 0 和 1
再看 左半边 和 右半边 的奇偶性
如果点数是奇数, 则为 "1 0 1 0 ... 2"的形式, 如果是偶数, 则为 "1 0 1 0 1 0"的形式

其中一侧的点数为 y - x - 1
另一侧点数为 n - y + x - 1

如果两边都是偶数, 那么可以是 "1 0 1 0 1 0"的形式
如果两边都是奇数, 那么先设 a[(x + y) / 2] = 2, a[((y + x + n) / 2) % n] = 2

*/