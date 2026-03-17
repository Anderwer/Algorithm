#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

string get(int x)
{
    string s;
    while(true)
    {
        string t = to_string(x);
        s += t;
        if(x < 10) break;
        int y = 0;
        for(auto c : t) y += c - '0';
        x = y;
    }
    return s;
}

void solve()
{
    string s;
    cin >> s;

    vector<int> cnt(10, 0);
    int sum = 0, n = s.size();
    for(auto c : s)
    {
        cnt[c - '0']++;
        sum += c - '0';
    }

    for(int x = 1; x <= sum; x++)
    {
        string t = get(x);
        vector<int> need(10, 0), rem = cnt;
        int val = 0;
        for(auto c : t)
        {
            need[c - '0']++;
            val += c - '0';
        }

        bool ok = true;
        for(int i = 0; i <= 9; i++)
        {
            if(need[i] > rem[i]) ok = false;
            rem[i] -= need[i];
        }
        if(!ok) continue;

        if(t.size() == n)
        {
            if(x < 10)
            {
                cout << t << "\n";
                return;
            }
            continue;
        }

        if(sum - val != x) continue;

        int len = n - t.size();
        int first = -1;
        for(int i = 1; i <= 9; i++)
        {
            if(rem[i])
            {
                first = i;
                break;
            }
        }
        if(first == -1) continue;

        string ans;
        ans += char('0' + first);
        rem[first]--;

        for(int i = 0; i <= 9; i++)
        {
            while(rem[i]--)
            {
                ans += char('0' + i);
            }
        }

        if(ans.size() != len) continue;
        cout << ans << t << "\n";
        return;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--)
    {
        solve();
    }
    return 0;
}