典型应用 : 给定字符串A和字符串B,求B在A里出现的次数

字符串哈希公式 : Hash(s) = Σ[1,n](c[i] * base^(n - i)) % p;
字符串哈希步骤 :
    1.设定 const int p = 9999971, base为大于max(c[i]) 的素数

    2.初始化c[0] = 1,预处理 c[i] = c[i - 1] * base % p;

    3.预处理字符串A的哈希数组 ha[i] = (ha[i - 1] * base + a[i] - 'a') % p;

    4.预处理字符串B的哈希数组 hb[i] = (hb[i - 1] * base + b[i] - 'a') % p;

    5.遍历字符串A的哈希数组,统计与hb[m]相同的哈希值的数量 if((ha[i + m - 1] - 1LL * ha[i - 1] * c[m] % p + p) % p == hb[m]) ans++;

例题 : 字串查找

#include<bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 1e6 + 10;
const int p = 9999971;
const int base = 101;
int pa[N],pb[N],c[N];

void solve()
{
	string a,b;
    cin >> a >> b;
    a = " "  + a;
    b = " " + b;
    int n = a.size() - 1;
    int m = b.size() - 1;
    c[0] = 1;
    for(int i = 1; i <= n; i++) c[i] = c[i - 1] * base % p;
    for(int i = 1; i <= n; i++)
    {
        if(a[i] >= 'a' && a[i] <= 'z') pa[i] = (pa[i - 1] * base + a[i] - 'a') % p;
        else pa[i] = (pa[i - 1] * base + a[i] - 'A') % p;
    }
    for(int i = 1; i <= m; i++)
    {
        if(b[i] >= 'a' && b[i] <= 'z') pb[i] = (pb[i - 1] * base + b[i] - 'a') % p;
        else pb[i] = (pb[i - 1] * base + b[i] - 'A') % p;
    }
    int ans = 0;
    for(int i = 1; i + m - 1 <= n; i++)
    {
        if((pa[i + m - 1] - 1LL * pa[i - 1] * c[m] % p + p) % p == pb[m]) ans++;
    }
    cout << ans << "\n";
}