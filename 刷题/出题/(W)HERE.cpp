#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n, x, y;
    cin >> n >> x >> y;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    int pos;
    for(int i = 1; i <= n; i++)
        if(a[i] == 5) pos = i;

    int pre = pos - x; //前 x 位, pre 可能小于 1
    int suf = pos + y; //后 y 位, suf 可能大于 n
    while(pre < 1) pre += n;
    while(suf > n) suf -= n;
    cout << pos << " " << a[pre] << " " << a[suf] << "\n";
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    solve();
    return 0;
}
