#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

struct node
{
    int p, v;
    bool operator<(const node& b) const
    {
        return p < b.p;
    }
};

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<node> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i].p >> a[i].v;

    sort(a.begin() + 1, a.end());
    
    
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
