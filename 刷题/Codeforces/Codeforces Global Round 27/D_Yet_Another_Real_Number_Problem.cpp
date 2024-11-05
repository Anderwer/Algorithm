#include <bits/stdc++.h>
#define int long long
using namespace std;
using i64 = long long;
const int N = 2e5 + 10;
const int p = 1e9 + 7;
i64 a[N], pre[N];
i64 cnt[N];

int qpow(int a, int b)
{
    int res = 1;
    while(b)
    {
        if(b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

bool check(int i, int x)
{
    if(cnt[i] - cnt[x] > 30) return true;
    return a[x] <= a[i] * (1LL << (cnt[i] - cnt[x]));
}

void solve()
{
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i], cnt[i] = 0;
    for(int i = 1; i <= n; i++)
    {
        cnt[i] = cnt[i - 1];
        while(~a[i] & 1) a[i] /= 2, cnt[i]++;
        pre[i] = (pre[i - 1] + a[i]) % p;
    }
    
    i64 sum = 0;
    stack<i64> st;
    for(int i = 1; i <= n; i++)
    {
        while(!st.empty() && check(i, st.top()))
        {
            int pos = st.top(), last = 0;
            st.pop();
            if(!st.empty()) last = st.top();
            sum = ((sum - a[pos] % p * qpow(2, cnt[pos] - cnt[last])) % p + a[pos] + p) % p;  
        }

        int last = 0;
        if(!st.empty()) last = st.top();
        sum = ((sum + a[i] % p * qpow(2, cnt[i] - cnt[last])) % p - a[i] + p) % p;
        cout << (sum % p + pre[i] % p + p) % p << " ";
        st.push(i);
    }
    cout << "\n";
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t = 1;
    cin >> t;
    while(t--) solve();
    return 0;
}
/*
我们先用一个 cnt[i] 记录前 i 个位置一共能除出多少个2, 此时也让 a[i] 变动

对于一个序列
        4 8 3 8 7
cnt[i]: 2 5 5 8 8
a[i]  : 1 1 3 1 7
        4
        1 32
        1 1 96
    x   1 1 96 8
        1 1 3 256
    x   1 1 3 256 7
        1 1 3 1 1792

我们可以用一个单调栈维护当前的最大值, 如果 a[i] * qpow(2, cnt[i] - cnt[st.top()]) >= a[st.top()], 则将栈顶弹出, 因为此时把 2 乘到 a[i] 上更优
*/