#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

int LIS(string& a) // a[1] 开始
{
    int len = 0;
    vector<int> f(a.size() + 1, 0);
    for(int i = 1; i < a.size(); i++)
    {
        if(a[i] > f[len]) f[++len] = a[i];
        else f[lower_bound(f.begin() + 1, f.begin() + len + 1, a[i]) - f.begin()] = a[i];
    }
    return len;
}

void solve()
{
    string s, k;
    cin >> s >> k;
    set<char> st;
    for(auto v : s) st.insert(v);

    if(k.size() > 2) cout << st.size() << "\n";
    else
    {
        int kk = stoi(k);
        if(kk >= 26) cout << st.size() << "\n";
        else
        {
            string cur = " ";
            for(int i = 1; i <= kk; i++) cur += s;
            cout << LIS(cur) << "\n";
        }
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
