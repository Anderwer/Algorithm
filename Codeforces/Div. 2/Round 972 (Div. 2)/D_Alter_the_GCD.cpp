#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i];

    vector<int> pre_a(n + 1), pre_b(n + 1);
    for(int i = 0; i < n; i++)
    {
        pre_a[i + 1] = gcd(pre_a[i], a[i]);
        pre_b[i + 1] = gcd(pre_b[i], b[i]);
    }

    vector<int> suf_a(n + 1), suf_b(n + 1);
    for(int i = n - 1; i >= 0; i--)
    {
        suf_a[i] = gcd(suf_a[i + 1], a[i]);
        suf_b[i] = gcd(suf_b[i + 1], b[i]);
    }

    vector<array<int, 2>> pa, pb; //pa[i][0] = 位置最后的gcd, pa[i][1] = 该gcd的下标 
    for(int i = 0; i <= n; i++)
    {
        if(i == n || pre_a[i] != pre_a[i + 1]) pa.push_back({pre_a[i], i});
        if(i == n || pre_b[i] != pre_b[i + 1]) pb.push_back({pre_b[i], i});
    }
    
    i64 max_gcd = 0, cnt = 0;
    vector<array<int, 2>> sa{{0, 0}}, sb{{0, 0}}; // 记录区间[i, r)的后缀gcd
    for(int r = 1; r <= n; r++) //枚举区间右端点
    {
        int gcd_r = a[r - 1];
        for(int i = sa.size() - 1; i >= 0; i--) //从右往左的递推gcd
        {
            gcd_r = gcd(gcd_r, sa[i][0]);
            sa[i][0] = gcd_r;
        }
        int pos = 0;
        for(int i = 0; i < (int)sa.size(); i++)
        {
            if(pos > 0 && sa[pos - 1][0] == sa[i][0]) sa[pos - 1][1] = sa[i][1]; //记录位置最后的gcd
            else sa[pos++] = sa[i];
        }
        sa.resize(pos); //减小为log 个不同的gcd
        sa.push_back({0, r}); //因为记录的区间是[i,r - 1],因此将r处的gcd设为0

        //对b数组也进行以上操作
        gcd_r = b[r - 1];
        for(int i = sb.size() - 1; i >= 0; i--)
        {
            gcd_r = gcd(gcd_r, sb[i][0]);
            sb[i][0] = gcd_r;
        }
        pos = 0;
        for(int i = 0; i < (int)sb.size(); i++)
        {
            if(pos > 0 && sb[pos - 1][0] == sb[i][0]) sb[pos - 1][1] = sb[i][1]; 
            else sb[pos++] = sb[i];
        }
        sb.resize(pos);
        sb.push_back({0, r});

        int pos_pa = 0, pos_pb = 0, pos_sa = 0, pos_sb = 0, last = -1;
        while(true)
        {           
                    //也就是交换区间[u, r-1], 此时的u作为区间左端点
                    //因为pa, pb, sa, sb四个数组中数量都只有log 个, 因此暴力枚举
            int u = min({pa[pos_pa][1], pb[pos_pb][1], sa[pos_sa][1], sb[pos_sb][1]});
            if(u >= r) break; //枚举出界
            if(u > last) //防止重数
            {               //区间组成为 a[0,u-1] b[u, r-1] a[r, n-1]
                int ans = gcd(pa[pos_pa][0], gcd(sb[pos_sb][0], suf_a[r])) +
                          gcd(pb[pos_pb][0], gcd(sa[pos_sa][0], suf_b[r]));
                if(max_gcd < ans) //需要更新max_gcd
                {
                    max_gcd = ans;
                    cnt = u - last; // 当前定位为左端点u的最右边, 减去上一个左端点的最右边则为统计数
                }
                else if(max_gcd == ans) cnt += u - last;
            }
            last = u; //下一轮枚举
            if(pa[pos_pa][1] == u) pos_pa++;
            if(pb[pos_pb][1] == u) pos_pb++;
            if(sa[pos_sa][1] == u) pos_sa++;
            if(sb[pos_sb][1] == u) pos_sb++; // 更新一下不同的gcd位置
        }
    }
    cout << max_gcd << " " << cnt << "\n"; 
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
