#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

bool check(int num, int x) //判断一个数是否含数字 x
{
    while(num > 0)
    {
        if(num % 10 == x) return true;
        num /= 10;
    }
    return false;
}

void solve()
{
    int n, x;
    cin >> n >> x;
    if(check(n, x))
    {
        for(int i = 1; i <= n; i++) cout << i << "\n";
    }
    else
    {
        for(int i = 1; i <= n; i++)
            if(check(i, x) == false) cout << i << "\n";
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    solve();
    return 0;
}
