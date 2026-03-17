#include <bits/stdc++.h>
#define int long long
using i64 = long long;
using namespace std;

const int N = 1e5 + 10;
int d[N], a[N];

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    for(int i = 1; i <= n; i++) cin >> d[i] >> a[i];
    d[n + 1] = 2e9;
    stack<pair<int, int>> st;
    int ans = 0;
    for(int i = 1; i <= n; i++) 
    {
        st.push({d[i], a[i]});
        int milk = (d[i + 1] - d[i]) * m; //这个区间的总牛奶需求量
        int sum = 0, need = 0;
        int start_day = d[i];
        
        while(!st.empty() && sum < milk)
        {
            pair<int, int> now = st.top();
            if(now.first + k <= start_day) break;//过期
            st.pop();
            int end_day = now.first + k - 1; //计算一下结束日期
            int has = min(now.second, (end_day - start_day + 1) * m - need); //特判处理一下是否a[i]溢出了当前区间最大
            if(sum + has >= milk) //这个区间的牛奶还有剩
            {
                has -= (milk - sum);
                sum = milk;
                st.push({now.first, has});
            }
            else //这个区间的牛奶不够，需要之前日期的
            {
                sum += has;
                start_day = d[i] + sum / m; //更新一下起始日期
                need = sum % m; //还需要多少牛奶
            }
        }
        ans += sum / m;
    }
    cout << ans << "\n";

}
signed main()
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
先把 d[i] 天添加到stack中

计算一下day = d[i + 1] - d[i] 是多少天
这段区间所需牛奶数milk = day * m;
sum 为当前喝了多少
start_day = d[i] 获取当前日期
need 统计如果今天的不够喝，还需要喝多少之前的

*/