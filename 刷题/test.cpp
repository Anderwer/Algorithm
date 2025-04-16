#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    set<int> st;
    for(int i = 1; i <= 3; i++)
    {
        int x; cin >> x;
        st.insert(x);
    }
    for(auto it : st) cout << it << " ";
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
