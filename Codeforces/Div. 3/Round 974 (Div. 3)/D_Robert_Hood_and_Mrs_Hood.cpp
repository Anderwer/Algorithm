#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

const int N = 1e5 + 10;
int Left[N];
int Right[N];
int preL[N], preR[N];

void solve()
{
    int n, d, k;
    cin >> n >> d >> k;
    for(int i = 1; i <= n; i++) Left[i] = Right[i] = preL[i] = preR[i] = 0;
    for(int i = 1; i <= k; i++)
    {
        int x, y;
        cin >> x >> y;
        Left[x]++;
        Right[y]++;
    }

    for(int i = 1; i <= n; i++)
    {
        preL[i] = preL[i - 1] + Left[i];
        preR[i] = preR[i - 1] + Right[i];
    }

    int ans1 = 0, ans2 = 0, mx = -1, mn = 1e9;

    for(int i = d; i <= n; i++)
    {
        int num = preL[i] - preR[i - d];
        if(num > mx)
        {
            mx = num;
            ans1 = i - d + 1;
        }
        if(num < mn)
        {
            mn = num;
            ans2 = i - d + 1;
        }
    }
    cout << ans1 << " " << ans2 << "\n";
    
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
前缀和
*/