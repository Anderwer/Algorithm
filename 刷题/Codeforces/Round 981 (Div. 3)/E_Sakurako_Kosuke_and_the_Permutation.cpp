#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 1e6 + 10;
int a[N];
int pos[N];

void solve()
{
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i], pos[a[i]] = i;
    
    int ans = 0;
    for(int i = 1; i <= n; i++)
    {
        if(a[i] == i || a[a[i]] == i) continue;
        int p = pos[i];
        pos[a[p]] = a[i];
        pos[a[a[i]]] = p;
        swap(a[a[i]], a[p]);
        ans++;
    }
    cout << ans << "\n";
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
当一个点 a[i] != i 时, 我们使其a[a[i]] = i, 这样一下能使两个点满足条件, 比让 a[i] = i 更好

假设现在有 a[i] = p, 则要让 a[p] = i
如果现在 a[p] != i, 则要找到等于 i 的位置 pos[i]
让 位置p 和位置 pos[i] 互换

*/