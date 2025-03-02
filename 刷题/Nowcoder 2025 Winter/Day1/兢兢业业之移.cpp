#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<vector<char>> a(n + 1, vector<char>(n + 1, '0'));
    for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) cin >> a[i][j];

    vector<array<int, 4>> ans;
    for(int i = 1; i <= n / 2; i++) //在左上角区域从上往下, 从左往右找一个是 0 的点, 则这个地方的左上方全都是 1
    {
        for(int j = 1; j <= n / 2; j++)
        {
            if(a[i][j] == '0')
            {
                int x = -1, y = -1;
                for(int l = 1; l <= n && x == -1; l++)
                {
                    for(int r = 1; r <= n && x == -1; r++)
                    {
                        if((l < i && r <= n / 2) || (l == i && r < j)) continue; //说明在以前操作过的地方
                        if(a[l][r] == '1')
                        {
                            x = l, y = r;
                            break;
                        }
                    }
                }

                while(x < i)
                {
                    swap(a[x][y], a[x + 1][y]);
                    ans.push_back({x, y, x + 1, y});
                    x++;
                }
                while(y < j)
                {
                    swap(a[x][y], a[x][y + 1]);
                    ans.push_back({x, y, x, y + 1});
                    y++;
                }
                while(y > j)
                {
                    swap(a[x][y], a[x][y - 1]);
                    ans.push_back({x, y, x, y - 1});
                    y--;
                }
                while(x > i)
                {
                    swap(a[x][y], a[x - 1][y]);
                    ans.push_back({x, y, x - 1, y});
                    x--;
                }
            }
        }
    }
    cout << ans.size() << "\n";
    for(auto [a_, b_, c_, d_] : ans) cout << a_ << " " << b_ << " " << c_ << " " << d_ << "\n";
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
直接枚举所有左上部分的点, 我们按行从上到下, 按列从左到右枚举.
那么如果我们枚举到了(i, j), 则区域 1 <= x < i, 1 <= y <= n / 2 和区域 x = i, 1 <= y < j 都是 1
如果(i, j)是 0, 我们找一个不在已经操作好的位置的 1 移过来即可
*/