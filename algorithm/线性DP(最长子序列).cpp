一.最长上升子序列(LIS)

1. O(N^2) 做法 : dp[i] 为串S前i个元素构成的最长子序列的长度

即 dp[i] = max(dp[i],dp[j] + 1); (1 < j < i)

最终答案 ans = max(dp[i]);

(1).初始化: dp[1] = 1;

(2).每个元素都作为出发点,二层循环遍历出发点前面所有的元素,如果前面存在a[j] < a[i] 则将进行状态转移

(3).得到最大长度ans

具体实现: 略

2. O(NlogN) 做法: dp[i] 为以i结尾的最长子序列的a长度

//最长上升子序列
int LIS(string& a) // a[1] 开始, string a 可以改成 vector<int> a
{
    int len = 0;
    vector<int> f(a.size() + 1, 0);
    for(int i = 1; i < a.size(); i++)
    {
        if(a[i] > f[len]) f[++len] = a[i];
        else f[lower_bound(f.begin() + 1, f.begin() + len + 1, a[i]) - f.begin()] = a[i];
    }
    return len;
}

二.最长不下降子序列(LNDS)

思路:只需将最长上升子序列中的if 里的 > 改成 >= ,lower_bound 改成 upper_bound

三.最长下降子序列(LDS)

思路:只需将最长上升子序列中的if 里的 > 改成 < ,lower_bound 重载 greater<int>()

四.最长不上升子序列(LNIS)

思路:只需将最长下降子序列中的if 里的 < 改成 <= ,lower_bound 改成 upper_bound 并重载 greater<int>()

值得一提的是:
    由Dilworth定理可知,最大反链中元素的数目必等于最小链划分中链的数目.则有以下四个结论:
    1.最长上升子序列的个数 = 最长不上升子序列的长度

    2.最长下降子序列的个数 = 最长不下降子序列的长度

    3.最长不上升子序列的个数 = 最长上升子序列的长度
    
    4.最长不下降子序列的个数 = 最长下降子序列的长度
