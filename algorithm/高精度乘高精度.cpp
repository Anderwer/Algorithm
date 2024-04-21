#include<array>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn = 1000000;
typedef array<int, maxn> Arraymaxn;
Arraymaxn a{ 0 }, b{ 0 };//初始化
int t = 1;

int cut(int x, Arraymaxn& y)
{
    if (x == 0) return 1;
    int i = 0;
    while (x) {
        y[i] = x % 10;
        x /= 10;
        i++;
    }
    return i;
}

Arraymaxn mult(Arraymaxn& a, Arraymaxn& b, int a_, int b_)
{
    Arraymaxn res{ 0 };
    for (int i = 0; i < a_; i++) {
        for (int j = 0; j < b_; j++) {
            //if(i + j >= 500) continue;如果结果需要500位,可以剪枝
            res[i + j] += a[i] * b[j];
        }
    }
    //处理进位
    t = a_ + b_;//a位数乘b位数,结果有a+b位数
    for (int i = 0; i < t; i++) {
        if (res[i] >= 10) {
            res[i + 1] += res[i] / 10;
            res[i] %= 10;
            t = max(t, i + 1);
        }
    }
    return res;
}

Arraymaxn init(string x, int sz)
{
    int pos = 0;
    Arraymaxn tmp{ 0 };
    for (int i = sz - 1; i >= 0; i--) {
        tmp[pos++] = x[i] - '0';
    }
    return tmp;
}

int main()
{
    string x, y;
    cin >> x >> y;
    a = init(x, x.size());
    b = init(y, y.size());
    Arraymaxn ans;
    ans = mult(a, b, x.size(), y.size());
    while (ans[t] == 0) t--;//去除前导0
    for (int i = t; i >= 0; i--) cout << ans[i];
}