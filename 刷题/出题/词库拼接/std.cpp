#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 2E6 + 10;
const int charsize = 26;
int Trie[N + 1][charsize];
bool isend[N + 1];
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

bool search(string& s, int L, int R)
{
    int cur = 0;
    for(int i = L; i <= R; i++)
    {
        int x = s[i] - 'a';
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

    for(int i = 1; i <= n; i++) insert(a[i]);

    int ans = 0;
    for(int i = 1; i <= n; i++)
    {
        int len = a[i].size();
        for(int j = 0; j < len - 1; j++) //分割成 [0, j] 和 [j + 1, len - 1]
        {
            if(search(a[i], 0, j) && search(a[i], j + 1, len - 1)) ans++;
        }
    }
    cout << ans << "\n";
}

int main()
{
    //std::ios::sync_with_stdio(false);
    //std::cin.tie(nullptr);
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
