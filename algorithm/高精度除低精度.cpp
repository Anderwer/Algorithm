#include<array>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn = 1000000;
typedef array<int, maxn> Arraymaxn;
Arraymaxn a{ 0 };//初始化
int t = 1;//位数,自己修改

Arraymaxn div(Arraymaxn& tmp, int x)
{
    Arraymaxn ans{ 0 };
    long long k = 0;
    for (int i = t; i >= 0; i--) {
        ans[i] = (k * 10 + tmp[i]) / x;
        k = (k * 10 + tmp[i]) % x;
    }
    return ans;
}

int main()
{
    Arraymaxn a{ 0 };
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;//模拟321÷5
    int x = 5;
    t = 3;
    Arraymaxn ans = div(a, x);
    while (ans[t] == 0) t--;
    for (int i = t; i >= 0; i--) cout << ans[i];
    return 0;
}
