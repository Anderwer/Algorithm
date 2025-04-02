#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    for(int i = n - 1; i >= 1; i--)
    {
        if(a[i] > a[i + 1]) //需要进行分解操作
        {
            if(a[i] / 10 > a[i] % 10 || a[i] % 10 > a[i + 1]) //判断a[i]的十位是否小于等于个位, 并判断a[i]的个位是否小于等于a[i + 1]
            {
                cout << "NO\n";
                return;
            }
            else a[i] = a[i] / 10; //如果能分解, 则当前a[i] 分解成两个数, 取前面的十位作为新的a[i], 以便判断a[i - 1]的时候用
        }
    }
    cout << "YES\n"; //全部判断完成, 没输出过 No 则数组符合条件
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--) solve();
    return 0;
}