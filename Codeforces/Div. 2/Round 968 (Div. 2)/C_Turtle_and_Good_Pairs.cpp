#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 2e5 + 10;
int a[27];
char s[N];

void solve()
{
    int n;
    cin >> n;
    for(int i = 0; i < 26; i++) a[i] = 0;
    for(int i = 1; i <= n; i++)
    {
        char c; cin >> c;
        a[c - 'a']++;
    }
    
    for(int i = 1; i <= n; i++)
    {
        int mx = -1, ch;
        for(int j = 0; j < 26; j++) if(a[j] > mx) mx = a[j], ch = j;
        a[ch]--;
        cout <<(char)(ch + 'a');
    }
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


/*
要满足 s[i] == s[j] 数量最多, 怎么放都行

要满足 s[i] != s[k] || s[j] != s[k + 1], 假如选定一个区间 [i, j], 则 k 可以在 区间[i, j - 1] 里选择,
假设定下来一个 k , 则 k 左边的字符要尽量与 s[k] 不同, k + 1 右边的字符要尽量与 s[k + 1] 不同
如果一个子串 形如 aaaaaabbbbbb, 则在 "aaaaaa" 或是 "bbbbbb" 中的 <i,j> 都找不到合法的 k
因此, 要想更多满足, 则要尽可能交错放置字符
    
*/