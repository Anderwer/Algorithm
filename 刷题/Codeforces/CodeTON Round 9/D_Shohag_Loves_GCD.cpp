#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> a(m + 1);
    for(int i = 1; i <= m; i++) cin >> a[i];
    sort(a.begin() + 1, a.end(), greater<int>());

    vector<int> pos(n + 1, 0);
    pos[1] = 1;
    int cur = 0;
    for(int i = 1; i <= n; i++)
    {
        for(int j = i * 2; j <= n; j += i)
        {
            pos[j] = max(pos[j], pos[i] + 1);
            cur = max(cur, pos[j]);
        }
    }
    if(cur > m) cout << -1 << "\n";
    else
    {
        for(int i = 1; i <= n; i++) cout << a[pos[i]] << " ";
        cout << "\n";
    }
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
注意到, 当 i = 1 时, 约束条件变为 gcd(a[1], a[j]) != a[1], 而题目要求字典序最大, 因此 a[1] 放最大值, 且 所有能被 i 整除的 j 的位置不能放 a[1]
当 i = 2 时, 约束条件变为 gcd(a[2], a[j]) != a[2], 因此 a[2] 放次大值, 且所有能被 i 整除的 j 的位置不能放 a[2]
...
因此, 我们可以就这样模拟, 模拟时由于是调和级数 , O(nlogn)
*/