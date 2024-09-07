#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

const int p = 19260817;

template <typename T>
inline void read(T &x)//快读
{
    x = 0;
    int ch = getchar();
    while(!isdigit(ch) && ch != EOF) ch = getchar();
    while(isdigit(ch))
    {
        x = (x << 3) + (x << 1) + (ch - '0');
        x %= p;
        ch = getchar();
    }
}

int qpow(long long a, int b)
 {
    int ans = 1;
    a = (a % p + p) % p;
    for (; b; b >>= 1)
    {
        if (b & 1) ans = (a * ans) % p;
        a = (a * a) % p;
    }
    return ans % p;
}

void solve()
{
    int a, b;
    read(a);
    read(b);
    if(b % p == 0)
    {
        cout << "Angry!\n";
        return;
    }
    cout << ((i64)a * (i64)qpow(b, p - 2) % p + p) % p;
}

int main()
{
    solve();
    return 0;
}