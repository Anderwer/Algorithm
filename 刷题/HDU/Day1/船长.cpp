#include <bits/stdc++.h>
#define int long long
using i64 = long long;
using namespace std;
const int mod = 998244353;

void solve()
{
    int inv_2 = 499122177;
    i64 n, k, cur;
    cin >> n >> k >> cur;
    vector<int> a(k);
    vector<int> p(k, 1); //一开始将所有人的威胁概率设为 1
    for(int i = 0; i < k; i++)
    {
        cin >> a[i];
        a[i]--; //将每个敌人的编号都 -1, 这样做的好处是每两个对打的人的编号 / 2 都一样, 例如3, 4 两人对打, 他们 /2 之后的编号作为下一轮的编号使用
    }
    cur--;
    sort(a.begin(), a.end());
    
    i64 ans = 1;
    while(n > 1)
    {
        vector<int> new_a;
        vector<int> new_p;
        cur /= 2;
        for(int i = 0; i < a.size(); i++)
        {
            int enemy = a[i] / 2;
            if(enemy == cur)
            {
                ans = (ans * (1 - p[i] + mod) % mod + mod) % mod; // 和有威胁的人打
            }
            else
            {
                if(i + 1 < a.size() && enemy == (a[i + 1] / 2)) //两个人对打, 且两个人都是有威胁的人
                {
                    new_p.push_back((p[i] + p[i + 1]) * inv_2 % mod);
                    i++; //因为算了2个人, i + 1 也不用算了
                }
                else new_p.push_back(p[i] * inv_2 % mod);
                new_a.push_back(enemy); //把打完后的编号加进去
            }
        }

        a = new_a;
        p = new_p;
        n = (n + 1) / 2; //向上取整, 处理 n 为奇数时的情况
    }
    cout << ans % mod << "\n";
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
