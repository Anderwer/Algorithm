#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

const int N = 2e5 + 10;
int a[N];
int ans[N];

void solve()
{
    int n, k, q;
    cin >> n >> k >> q;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) a[i] = a[i] - i;
    
    int l = 1, r = 1;
    map<int, int> cnt; //cnt[i]: 记录区间内数字为i的数量有多少
    map<int, set<int>, greater<int>> pos; // pos[i]: 记录一下区间里数量为 i 的都有哪些数
    while(l <= r && r <= n)
    {
        if(r - l + 1 < k)
        {
            pos[cnt[a[r]]].erase(a[r]);
            if(pos[cnt[a[r]]].empty()) pos.erase(cnt[a[r]]);
            cnt[a[r]]++;
            pos[cnt[a[r]]].insert(a[r]);
            r++;
            continue;
        }
        pos[cnt[a[r]]].erase(a[r]);
        if(pos[cnt[a[r]]].empty()) pos.erase(cnt[a[r]]);
        cnt[a[r]]++;
        pos[cnt[a[r]]].insert(a[r]);
        int mx = pos.begin() -> first;
        ans[l] = k - mx;
        
        pos[cnt[a[l]]].erase(a[l]);
        if(pos[cnt[a[l]]].empty()) pos.erase(cnt[a[l]]);
        cnt[a[l]]--;
        pos[cnt[a[l]]].insert(a[l]);
        l++;
        r++;
    }
    
    while(q--)
    {
        int l, r;
        cin >> l >> r;
        cout << ans[l] << "\n";
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
先将 a[i] 的每个元素变为 a[i] - i, 设为b[i]
这样如果原本a[i] 和 a[i + 1] 是连续的, 则 b[i] == b[i + 1]
由于区间长度固定为k
因此可以对b[i]进行滑动窗口维护一个区间出现的相同的数最多有多少, 这个区间的答案为k - maxn

cnt[0] = 3
cnt[-2] = 1
cnt[-4] = 1

*/