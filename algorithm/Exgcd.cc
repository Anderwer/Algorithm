
int Exgcd(int a, int b, int &x, int &y) {
  if (!b) {
    x = 1, y = 0;
    return a;
  }
  int d = Exgcd(b, a % b, x, y);
  int t = x;
  x = y, y = t - (a / b) * y;
  return d;
}

inline ll exgcd(ll a, ll b, ll &x, ll &y) {
  return !b ? (x = 1, y = 0, a) : (exgcd(b, a % b, y, x), y -= (a / b) * x);
}

//exgcd 用于求解 ax + by = gcd(a,b) 其中a,b互质的一组可行解
//如果a,b互质,则gcd(a,b) = 1,问题转化为 ax + by = 1
//exgcd 的结果只满足 |x| + |y| 最小
//结果需要 (x % b + b) % b 才能满足 x > 0
//其中,对于线性同余方程 ax = 1 (mod b) ,x 为 a mod b 的逆元,可用exgcd 求解
