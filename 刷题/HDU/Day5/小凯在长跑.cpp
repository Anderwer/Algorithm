#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
int d, r, x, y;

double dis_1()
{
    if (y >= -d && y <= d) return abs(x - r);
    double dist1 = hypot(x - r, y - d);
    double dist2 = hypot(x - r, y + d);
    return min(dist1, dist2);
}

double dis_2()
{
    if (y >= -d && y <= d) return abs(x + r);
    double dist1 = hypot(x + r, y - d);
    double dist2 = hypot(x + r, y + d);
    return min(dist1, dist2);
}

double dis_3()
{
    double len = hypot(x, y - d);
    if(len == 0) return r;
    double px = ((double)(x) / len) * r;
    double py = d + ((double)(y - d) / len) * r;
    if(py >= d) return abs(len - r);
    double dist1 = hypot(x - r, y - d);
    double dist2 = hypot(x + r, y - d);
    return min(dist1, dist2);
}

double dis_4()
{
    double len = hypot(x, y + d);
    if(len == 0) return r;
    double px = ((double)(x) / len) * r;
    double py = -d + ((double)(y + d) / len) * r;
    if(py <= -d) return abs(len - r);
    double dist1 = hypot(x - r, y + d);
    double dist2 = hypot(x + r, y + d);
    return min(dist1, dist2);
}

void solve()
{
    cin >> d >> r >> x >> y;

    double ans = min({dis_1(), dis_2(), dis_3(), dis_4()});
    cout << (int)(ans + 0.5) << "\n";
    
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--)
    {
        solve();
    }
    return 0;
}
