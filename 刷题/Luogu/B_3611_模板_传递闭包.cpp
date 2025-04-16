#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

struct Floyd
{
    int n;
    bitset<200> f[200]; //具体由 n 大小决定

    Floyd() {};
    Floyd(int n_): n(n_) {};

    void floyd()
    {
        for(int k = 1; k <= n; k++)
            for(int i = 1; i <= n; i++)
                if(f[i][k]) f[i] |= f[k];
    }
};

void solve()
{
    int n;
    cin >> n;
    
    Floyd F(n);
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
        {
            int w; cin >> w;
            F.f[i][j] = w;
        }

    F.floyd();
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++) cout << (int)F.f[i][j] << " ";
        cout << "\n";
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    while(t--)
    {
        solve();
    }
    return 0;
}
