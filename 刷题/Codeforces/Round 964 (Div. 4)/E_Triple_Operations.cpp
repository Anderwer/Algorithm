#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 2e5 + 10;
int pre[N];

void init()
{
    for(int i = 1; i < N; i++)
    {
        int num = i, cnt = 0;
        while(num)
        {
            num /= 3;
            cnt++;
        }
        pre[i] = pre[i - 1] + cnt;
    }
}

void solve()
{
    int L, R;
    cin >> L >> R;
    cout << pre[R] - pre[L] + 2 * (pre[L] - pre[L - 1]) << "\n";
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    cin >> t;
    init();
    while(t--){
        solve();
    }
    return 0;
}
