一. 欧几里得算法 : 

int gcd(int a, int b)
{
    if(b == 0) return a;
    return gcd(b, a % b);
}

二. 裴蜀定理 
    : 任意整数a, b, d 且有 gcd(a,b) | d  <======>  存在整数u, v 使得 ua + vb = d

三. 扩展欧几里得算法 : 用于求解 ax + by = gcd(a, b) 的整数解x, y

int exgcd(int a, int b, int& x, int& y)
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

对于求解 ax + by = gcd(a, b) 的情况:
直接通过exgcd求出一组最小解 x0, y0
之后可得出其通解:
x = x0 + (b / gcd(a, b)) * t;
y = y0 + (a / gcd(a, b)) * t;
枚举 t 即可找到最小非负解

对于求解 ax + by = d 的情况:
先求 ax + by = gcd(a, b)
此时特判, 如果 d % gcd(a, b) != 0, 则不存在解
对上式求exgcd, 得到x0, y0, 再让 a /= gcd(a, b) 且 b /= gcd(a, b) 且 d /= gcd(a, b)
此时有 ax0 + by0 = 1
让 x1 = x0 * d, y1 = y0 * d
此时有 ax1 + by1 = d

之后可得出其通解:
x = x1 + (b / gcd(a, b)) * t;
y = y1 - (a / gcd(a, b)) * t;
此时特判,  如果 y1 < 0, 则不存在非负整数解

