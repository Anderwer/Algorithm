#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 1e6 + 10;
const int M = 1e5 + 10;
const int charsize = 26;

int nxt[N + 1][charsize];
int num[N + 1][charsize];
bool isend[N + 1];
int root = 0, cnt = 0;

void insert(string& s, int id)
{
    int now = 0;
    for(auto& c : s)
    {
        int x = c - 'a';
        if(!nxt[now][x]) nxt[now][x] = ++cnt;
        num[now][x]++;
        now = nxt[now][x];
    }
    isend[now] = true;
}

int search(string& s)
{
    int now = 0, res = 0;
    int len = s.size();
    for(int i = 0; i < len; i++)
    {
        int x = s[i] - 'a';
        if(num[now][x] > 1) res++;
        now = nxt[now][x];
    }
    return res;
}

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<string> a(n + 1);
    for(int i = 1; i <= n; i++)
    {
        string s; cin >> a[i];
        insert(a[i], i);
    }
    while(q--)
    {
        int l, r;
        cin >> l >> r;
        int ans = cnt, Max = -1;
        for(int i = l; i <= r; i++)
        {
            int len = a[i].size();
            Max = max(Max, len);
        }
        cout << 2 * cnt - Max << "\n";
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
