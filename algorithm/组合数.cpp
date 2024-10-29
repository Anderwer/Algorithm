求单个组合数 : Lucas 定理

int qpow(int a, int b)
{
    int res = 1;
    while(b)
    {
        if(b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res % p;
}

int C(int a, int b)
{
    int ans = 1;
    int j = a;
    for(int i = 1; i <= b; i++, j--)
    {
        ans = ans * j % p;
        ans = ans * qpow(i, p - 2) % p;
    }
    return ans;
}

int lucas(int a, int b)
{
    if(a < p && b < p) return C(a, b);
    return C(a % p, b % p) * lucas(a / p, b / p) % p;
}

求多个组合数, 预处理 fact[N + 1] 和 infact[N + 1] (N <= 2e5)

int qpow(int a, int b)
{
    int res = 1;
    while(b)
    {
        if(b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res % p;
}

void IComb()
{
    fact[0] = 1;
    for(int i = 1; i <= N; i++) fact[i] = (fact[i - 1] * i) % p;
    infact[N] = qpow(fact[N], p - 2);
    for(int i = N - 1; i >= 0; i--) infact[i] = (infact[i + 1] * (i + 1)) % p;
}

int C(int a, int b)
{
    if(b > a || b < 0) return 0;
    return (fact[a] * ((infact[b] * infact[a - b]) % p)) % p;
}
