#include <bits/stdc++.h>
using u64 = unsigned long long;
using namespace std;

mt19937_64 rnd(time(0));
const int N = 2e5 + 10;
const int M = 1e6 + 10;
int a[N];
u64 pre[N], Hash[M];

void solve()
{
    int n, q;
    cin >> n >> q;
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i];
        pre[i] = pre[i - 1] ^ Hash[a[i]];
    }

    while(q--)
    {
        int l, r;
        cin >> l >> r;
        if((r - l + 1) & 1)
        {
            cout << "NO\n";
            continue;
        }
        if((pre[r] ^ pre[l - 1]) == 0) cout << "YES\n";
        else cout << "NO\n";
    }
    
}
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    cin >> t;

    for(int i = 1; i <= 1e6; i++) Hash[i] = rnd();

    while(t--){
        solve();
    }
    return 0;
}

/*
如果只有2个不同的数 : 警长必输
如果只有2个相同的数 : 平局
三个数 a, b, c: 则警长必输

区间长度为奇数则必输
区间长度为偶数且区间内所有不同的数都有偶数个则才能平局


*/
