#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 2, 0);
    for(int i = 1; i <= n; i++) cin >> a[i];

    vector<array<int, 2>> pos;
    int l = 1;
    while(l <= n)
    {
        int r = l;
        set<int> st;
        while(r <= n)
        {
            if(st.size() < 2)
            {
                st.insert(a[r]);
                r++;
            }
            else if(st.count(a[r])) r++;
            else break;
        }
        if(st.size() == 1) break;
        int cur = r - 1;
        while(a[cur] == a[r - 1]) cur--;
        pos.push_back({l, r - 1});
        l = cur + 1;
    }

    int ans = 0;
    vector<int> b(n + 1, 0);
    
    for(auto [x, y] : pos)
    {
        for(int i = x, cur = 1; i <= y; i++, cur++)
        {
            if(a[i] == a[x]) b[cur] = 1;
            else b[cur] = -1;
        }
        for(int i = 1; i + x - 1 <= y; i++) b[i] += b[i - 1];
        unordered_map<int, int> cnt;
        for(int i = 0; i + x - 1 <= y; i++)
        {
            ans += cnt[b[i]];
            cnt[b[i]]++;
        }
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
