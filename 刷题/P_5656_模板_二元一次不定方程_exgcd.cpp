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
    a /= g;
    b /= g;
    c /= g;
    i64 x_1 = x * c;
    x_1 = (x_1 % b + b) % b;
    i64 y_1 = (c - a * x_1) / b;
    int gg = __gcd(a, b); // 此时方程变为 ax + by = c
    if(y_1 <= 0)
    {
        cout << x_1 << " ";
        while(y_1 <= 0) y_1 += a / gg;
        cout << y_1 << "\n";
        return;
    }
    int t1 = 0, t2 = 0, tmp1 = y_1, tmp2 = x_1;
    while(tmp1 > a / gg) tmp1 -= a / gg, t1++;
    while(tmp2 > b / gg) tmp2 -= b / gg, t2++;
    cout << t1 + t2 + 1 << " ";
    int x_min = x_1, y_max = y_1;
    int x_max = x_min + t1 * (b / gg);
    int y_min = y_max - t1 * (a / gg);
    cout << x_min << " " << y_min << " " << x_max << " " << y_max << "\n";
}   

signed main()
{
    int t;
    cin >> t;
    while(t--) solve();
    return 0;
}