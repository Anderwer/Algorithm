#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int N = 1010;
char mp[N][N];
int ans, n, m;

void check(int x, int y, int s, int p)
{
	if(x <= n / 2 || y <= m / 2) return;

	string ss = "";
	for(int j = p; j <= y; j++) ss += mp[s][j];
	for(int j = s + 1; j <= x; j++) ss += mp[j][y];
	for(int j = y - 1; j >= p; j--) ss += mp[x][j];
	for(int i = x - 1; i >= s + 1; i--) ss += mp[i][p];

	int len = ss.size() - 1;
	ss += ss;
	for(int i = 0;i <= len; i++)
	    if(i + 3 <= ss.size()-1 && ss[i] =='1' && ss[i + 1] == '5' && ss[i + 2] == '4' && ss[i + 3] =='3') ans++;

	check(x - 1, y - 1, s + 1, p + 1);
}

void solve()
{
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++) cin >> mp[i][j];
    
    ans = 0;
    check(n, m, 1, 1);
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t = 1;
    cin >> t;
    while(t--) solve();
    return 0;
}