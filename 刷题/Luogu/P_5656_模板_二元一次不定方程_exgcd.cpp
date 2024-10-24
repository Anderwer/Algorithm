#include <bits/stdc++.h>
#define int long long
using i64 = long long;
using namespace std;

int exgcd(int a, int b, int &x, int &y)
{
    if(b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    int d = exgcd(b, a % b, x, y);
    int k = x;
    x = y;
    y = k - (a / b) * y;
    return d;
}

int up(int m, int n) //上取整
{
    if(m % n == 0) return m / n;
    return m / n + 1;
}

void solve()
{
    int a, b, c, x, y;
    cin >> a >> b >> c;
    int g = exgcd(a, b, x, y);
    if(c % g)
    {
        cout << "-1\n";
        return;
    }
    x *= c / g;
    y *= c / g; //将 ax + by = (a, b) 结果乘上 c / (a, b)
    int x_min = (x % (b / g) + (b / g)) % (b / g);
    int y_min = (y % (a / g) + (a / g)) % (a / g);
    while(x_min <= 0) x_min += b / g;
    while(y_min <= 0) y_min += a / g;
    int x_max = (c - b * y_min) / a;
    int y_max = (c - a * x_min) / b;
    if(y_max <= 0)
    {
        cout << x_min << " " << y_min << "\n";
        return;
    }
    cout << (x_max - x_min) / (b / g) + 1 << " " << x_min << " " << y_min << " " << x_max << " " << y_max << "\n";
    
}   

signed main()
{
    int t;
    cin >> t;
    while(t--) solve();
    return 0;
}