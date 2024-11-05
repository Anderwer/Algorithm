#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

void solve()
{
    int n, max_pos = 0;
    cin >> n;
    int x = n, cnt = 0;
    while(x)
    {
        if(x & 1) max_pos = cnt;
        cnt++;
        x >>= 1;
    }
    if(n == 6)
    {
        cout << 7 << "\n";
        cout << "1 2 4 6 5 3\n";
        return;
    }
    if(n & 1)
    {
        cout << n << "\n";
        for(int i = 1; i <= n; i++)
        {
            if(i == 3 || i == 1 || i == n - 1 || i == n) continue;
            cout << i << " ";
        }
        cout << "3 1 " << n - 1 << " " << n << "\n";
    }
    else
    {
        cout << (int)pow(2, max_pos + 1) - 1 << "\n";
        int now = pow(2, max_pos);
        for(int i = 1; i <= n; i++)
        {
            if(i == 1 || i == 3 || i == now - 2 || i == now - 1 || i == n) continue;
            cout << i << " ";
        }
        cout << "3 1 " << now - 2 << " " << now - 1 << " " << n << "\n";
    }
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

/*
根据打表发现:
当 n 是奇数时, k 为 n
当 n 是偶数时, k 为 pow(2, max_pos + 1) - 1 , 其中 max_pos 为 n 的最高二进制位

对于 n 为奇数, 我们考虑如何构造 k :
    由于最后一步是 & 操作, n 的最后一位是 1, n - 1 的最后一位是 0
    我们可以让 n - 1 & n, 这样前几位都可以复制过来, 而最后一位要把 0 变成 1
    我们可以用 3 & 1, 这样能保留住最后一位的 1
    因此, 最后四个数操作步骤是 3 & 1 | n - 1 & 1 ----> n
    而这之前的操作是 |, 因此前面的数怎么排都行

对于 n 为偶数的情况, 考虑如果构造 pow(2, max_pos + 1) - 1, 即前 max_pos 位全是 1:
    由于最后一步是 | 操作, n 中肯定包含 最高位的 1, pow(2, max_pos) - 1 包含前 max_pos - 1 位所有的 1
    我们可以让 pow(2, max_pos) - 1 | n, 这样就能构造出 k
    但是再往前一步是 & 操作, 我们必须让 pow(2, max_pos) - 1 的值不发生变化
    由于 pow(2, max_pos) - 1 是奇数, 因此最后一位是 1, 我们可以构造 3 & 1 | pow(2, max_pos) - 2 来维持不变
    因此, 最后五个数的操作步骤是 3 & 1 | pow(2, max_pos) - 2 & pow(2, max_pos) - 1 | n

*/