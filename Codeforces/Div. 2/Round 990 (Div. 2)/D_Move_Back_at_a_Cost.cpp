#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    
    vector<int> b;
    stack<int> stk;
    int mn = 1E9 + 10;
    for(int i = 1; i <= n; i++)
    {
        if(stk.empty())
        {
            stk.push(a[i]);
            continue;
        }
        while(!stk.empty() && a[i] < stk.top())
        {
            b.push_back(stk.top());
            mn = min(mn, stk.top());
            stk.pop();
        }
        stk.push(a[i]);
    }

    vector<int> ans;
    while(!stk.empty())
    {
        if(stk.top() > mn + 1) b.push_back(stk.top());
        else ans.push_back(stk.top());
        stk.pop();
    }
    sort(b.begin(), b.end());
    reverse(ans.begin(), ans.end());
    for(auto v : b) ans.push_back(v + 1);
    for(auto v : ans) cout << v << " ";
    cout << "\n";
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
