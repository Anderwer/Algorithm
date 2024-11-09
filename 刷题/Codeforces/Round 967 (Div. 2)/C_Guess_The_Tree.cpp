#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
vector<pair<int, int>> ans;

int query(int a, int b)
{
    int res;
    cout << "? " << a << " " << b << endl;
    cin >> res;
    return res;
}

void dfs(int a, int b)
{
    int res = query(a, b);
    if(a == res)
    {
        ans.push_back(make_pair(a, b));
        return;
    }
    dfs(res, b);
}

void solve()
{
    int n;
    cin >> n;
    ans.clear();
    for(int i = 2; i <= n; i++) dfs(1, i);
    cout << "! ";
    for(auto [x, y] : ans) cout << x << " " << y << " ";
    cout << "\n";
}

int main()
{
    //std::ios::sync_with_stdio(false);
    //std::cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
