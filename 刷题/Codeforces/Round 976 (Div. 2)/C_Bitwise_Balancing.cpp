#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

int _a[64], _b[64], _c[64], _d[64];
i64 b, c, d;

void init()
{
    int pos_b = 0, pos_c = 0, pos_d = 0;
    while(b)
    {
        if(b & 1) _b[pos_b++] = 1;
        else _b[pos_b++] = 0;
        b >>= 1;
    }
    while(c)
    {
        if(c & 1) _c[pos_c++] = 1;
        else _c[pos_c++] = 0;
        c >>= 1;
    }
    while(d)
    {
        if(d & 1) _d[pos_d++] = 1;
        else _d[pos_d++] = 0;
        d >>= 1;
    }
}

void solve()
{
    cin >> b >> c >> d;
    for(int i = 0; i < 64; i++) _a[i] = _b[i] = _c[i] = _d[i] = 0;
    init();
    bool flag = true;
    for(int i = 0; i < 64; i++)
    {
        if(_d[i] == 0)
        {
            if(_b[i] == 1 && _c[i] == 1) _a[i] = 1;
            else if(_b[i] == 0 && _c[i] == 1) _a[i] = 0;
            else if(_b[i] == 0 && _c[i] == 0) _a[i] = 0;
            else flag = false;
        }
        else 
        {
            if(_b[i] == 1 && _c[i] == 1) _a[i] = 0;
            else if(_b[i] == 0 && _c[i] == 0) _a[i] = 1;
            else if(_b[i] == 1 && _c[i] == 0) _a[i] = 0;
            else flag = false;
        }
    }
    if(flag == false)
    {
        cout << -1 << "\n";
        return;
    }
    else
    {
        i64 ans = 0;
        for(int i = 0; i < 64; i++) if(_a[i] == 1) ans += (1LL << i);
        if(ans <= (1LL << 61)) cout << ans << "\n";
        else cout << -1 << "\n";
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
对每一位二进制进行判断
当 _d[i] = 0 时, 必须满足 _a[i] | _b[i] == _a[i] & _c[i]
    当 _b[i] = 1, _c[i] = 1 时, _a[i] = 1
    当 _b[i] = 0, _c[i] = 1 时, _a[i] = 0 或 1
    当 _b[i] = 1, _c[i] = 0 时, 不成立
    当 _b[i] = 0, _c[i] = 0 时, _a[i] = 0

当 _d[i] = 1 时, 必须满足 _a[i] | _b[i] != _a[i] & _c[i]
    当 _b[i] = 1, _c[i] = 1 时, _a[i] = 0, 不借位
    当 _b[i] = 0, _c[i] = 1 时, 不成立
    当 _b[i] = 1, _c[i] = 0 时, _a[i] = 0 或 1, 不借位
    当 _b[i] = 0, _c[i] = 0 时, _a[i] = 1, 不借位
*/