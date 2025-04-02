#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 2E6 + 10;
const int charsize = 26;
int Trie[N][charsize];
bool isend[N];
int cnt = 0;

void insert(string& s)
{
    int cur = 0;
    for(auto c : s)
    {
        int x = c - 'a';
        if(!Trie[cur][x]) Trie[cur][x] = ++cnt;
        cur = Trie[cur][x];
    }
    isend[cur] = true;
}

bool search(string& s)
{
    int cur = 0;
    for(auto c : s)
    {
        int x = c - 'a';
        if(!Trie[cur][x]) return false;
        cur = Trie[cur][x];
    }
    return isend[cur];
}

void solve()
{
    int n;
    cin >> n;
    vector<string> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    for(int i = 1; i <= n; i++)
        insert(a[i]);

    int ans = 0;
    for(int i = 1; i <= n; i++)
    {
        int len = a[i].size();
        for(int j = 1; j < len; j++) //分割成 [0, j - 1] 和 [j, len - 1]
        {
            string pre = a[i].substr(0, j);
            string suf = a[i].substr(j);
            if(search(pre) && search(suf)) ans++;
        }
    }
    cout << ans << "\n";
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    solve();
    return 0;
}
