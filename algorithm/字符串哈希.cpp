
struct Hash
{
    const int mod1 = 100663319;
    const int mod2 = 201326611;
    const i64 P1 = 131;
    const i64 P2 = 13331;
    vector<i64> p1, p2, h1, h2, t1, t2;

    void init(string& s)
    {
        int n = s.size() - 1;
        p1.assign(n+1,0); p2.assign(n+1,0);
        h1.assign(n+1,0); h2.assign(n+1,0);
        t1.assign(n+2,0); t2.assign(n+2,0);
        p1[0] = p2[0] = 1;
        for(int i = 1; i <= n; i++)
        {
            p1[i] = p1[i - 1] * P1 % mod1;
            p2[i] = p2[i - 1] * P2 % mod2;
            h1[i] =(h1[i - 1] * P1 % mod1 + s[i] - '0' + 1) % mod1;
            h2[i] =(h2[i - 1] * P2 % mod2 + s[i] - '0' + 1) % mod2;
        }
        for(int i = n; i >= 1; i--)
        {
            t1[i] = (t1[i + 1] * P1 % mod1 + s[i] - '0' + 1) % mod1;
            t2[i] = (t2[i + 1] * P2 % mod2 + s[i] - '0' + 1) % mod2;
        }
    }

    int getHash1(int L, int R)
    {
        return (h1[R] - (h1[L - 1] * p1[R - L + 1]) % mod1 + mod1) % mod1;
    }

    int getHash2(int L, int R)
    {
        return (h2[R] - (h2[L - 1] * p2[R - L + 1]) % mod2 + mod2) % mod2;
    }

    int getRevHash1(int L, int R)
    {
        return (t1[L] - (t1[R + 1] * p1[R - L + 1]) % mod1 + mod1) % mod1;
    }

    int getRevHash2(int L, int R)
    {
        return (t2[L] - (t2[R + 1] * p2[R - L + 1]) % mod2 + mod2) % mod2;
    }
};
