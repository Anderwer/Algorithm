#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 2e5 + 10;

int a[N], b[N];

void solve()
{
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> mark(n + 1, 0);
    vector<int> pre;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= m; i++) cin >> b[i];

    for(int i = 1; i <= m; i++)
    {
        if(mark[b[i]] == 0)
        {
            mark[b[i]] = 1;
            pre.push_back(b[i]);
        }
    }

    int pos = 1;
    for(auto v : pre)
    {
        if(v == a[pos]) pos++;
        else
        {
            cout << "TIDAK\n";
            return;
        }
    }
    cout << "YA\n";
    
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
记录一下 b 数组中每个数的最早出现的序列, 如果和 a 的前缀一样, 则是好的
*/