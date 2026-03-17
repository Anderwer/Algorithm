#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    set<int> s1, s2;
    for(int i = 1; i <= n; i++)
    {
        if(a[i] == 1) s1.insert(i);
        if(a[i] == 2) s2.insert(i);
    }

    vector<array<int, 2>> ans;
    for(int i = n; i >= 1; i--)
    {
        if(a[i] == 2)
        {
            s2.erase(i);
            continue;
        }
        if(a[i] == 1) 
        {
            if(s2.empty())
            {
                s1.erase(i);
                continue;
            }
            int pos = *s2.begin();
            s2.erase(pos);
            swap(a[i], a[pos]);
            s1.erase(i);
            s1.insert(pos);
            ans.push_back({i, pos});
            continue;
        }
        if(s2.empty()) //处理 0
        {
            if(s1.empty()) break;
            int pos = *s1.begin();
            s1.erase(pos);
            swap(a[i], a[pos]);
            ans.push_back({pos, i});
        }
        else
        {
            int pos1 = *s1.begin();
            int pos2 = *s2.begin();
            s2.erase(pos2);
            s1.erase(pos1);
            a[i] = 2, a[pos1] = 0, a[pos2] = 1;
            s1.insert(pos2);
            ans.push_back({i, pos1});
            ans.push_back({i, pos2});
        }
    }

    cout << ans.size() << "\n";
    for(auto [x, y] : ans) cout << x << " " << y << "\n";
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
用两个 set 记录 1,2 的位置, 然后从后往前遍历, 如果当前走到了 1,2 就从集合里删掉
对于 0 来说, 如果前面还有 2, 就从集合中找出一个 1 进行交换, 再找出一个 2 进行交换
如果前面没有 2, 就找 1 进行交换
如果前面连 1 都没有, 就退出交换
对于 1 来说, 如果前面有 2 就进行交换, 否则退出
*/