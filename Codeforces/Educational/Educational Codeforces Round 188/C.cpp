#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

i64 lcm(i64 a, i64 b)
{
    return a / gcd(a, b) * b;
}

void solve()
{
    i64 a, b, c, m;
    cin >> a >> b >> c >> m;

    i64 ab = lcm(a, b), ac = lcm(a, c), bc = lcm(b, c), abc = lcm(ab, c);

    i64 x = m / a, y = m / b, z = m / c;
    i64 xy = m / ab, xz = m / ac, yz = m / bc, xyz = m / abc;

    cout << 6 * x - 3 * xy - 3 * xz + 2 * xyz << " ";
    cout << 6 * y - 3 * xy - 3 * yz + 2 * xyz << " ";
    cout << 6 * z - 3 * xz - 3 * yz + 2 * xyz << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--)
    {
        solve();
    }
    return 0;
}
