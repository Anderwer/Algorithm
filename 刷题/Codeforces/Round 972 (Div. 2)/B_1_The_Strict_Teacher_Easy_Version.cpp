#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

const int N = 1e5 + 10;
int b[N];
int c[N];
void solve()
{
    int n,m,q;
    cin >> n >> m >> q;
    for(int i = 1; i <= m; i++) cin >> b[i], c[i] = b[i];
    sort(b + 1, b + 1 + m);
    sort(c + 1, c + 1 + m, greater<int>());
    for(int i = 1; i <= q; i++)
    {
        int mx = b[m], mn = b[1];
        int pos, ans = 0;
        cin >> pos;
        if(mx < pos)
        {
            ans = n - mx;
        }
        else if(mn > pos)
        {
            ans = mn - 1;
        }
        else
        {
            int p_r = upper_bound(b + 1, b + 1 + m, pos) - b;
            int p_l = upper_bound(c + 1, c + 1 + m, pos, greater<int>()) - c;
            int left = c[p_l], right = b[p_r];
            ans = (right - left) / 2;
        }
        cout << ans << "\n";
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
/*
教师都在David左边: 3 6 8 , ans = n - pos + pos - 离David最近的教师 = n - 离David最近的教师

教师都在David右边: ans = pos - 1 + 离David最近的教师 - pos = 离David最近的教师 - 1

教师在David两边: ans =

当 (pos + left) % 2 == 0 时, 向左走  (pos - left)/2 步(包含停一步)，此时pos = pos - (pos - left)/2 + 1, right -= (pos - left)/2
当 (pos + left) % 2 == 1 时, 向左走  (pos - left)/2 步(没有停一步), 此时pos = pos - (pos - left)/2, right -= (pos - left)/2
当 (right - pos) % 2 == 0  时 ans += (right - pos) / 2;
当 (right - pos) % 2 == 1  时 ans += (right - pos) / 2 + 1;

1 4 10
--------
2 5 9
3 6 8
4 5 8
5 6 7
6 6 6
--------
2 3 10
3 4 9
4 5 8
5 6 7
6 6 6


1 2 4

while(pos - left != 1) pos--, left++, ans++;
1 6
2 5
3 4 -- 2步

1 7
2 6
3 5
4 5 -- 3步 ans += (pos - left) / 2;

1 6 10
2 5 9
3 4 8
4 5 7
5 6 6 -- 先走左,4步

1 6 10
2 7 9
3 7 8
4 6 7
5 5 6 -- 先走右,4步

2 6 10
3 5 9
4 5 8
5 6 7
6 7 7 -- 先走左,4步

2 6 10
3 7 9
4 7 8
5 6 7
6 6 6 -- 先走右,4步

1 5 10
2 4 9
3 4 8
4 5 7
5 6 6 

1 5 10
2 6 9
3 7 8
4 6 7
5 5 6

4 8
5 7
6 6 -- 2步

5 8
6 7
7 7 -- 2步

5 9
6 8
7 7

4 9
5 8
6 7
7 7 --3步
当 (right - pos) % 2 == 0  时 ans += (right - pos) / 2;
当 (right - pos) % 2 == 1  时 ans += (right - pos) / 2 + 1;

*/
