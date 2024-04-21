假如有以下长度为n的序列,以及一个大小为k的窗口,这个窗口从左往右移动,每次滑动一个单位,则每次窗口的最大值和最小值为:

[1   3  -1] -3   5   3   6   7
 1  [3  -1  -3]  5   3   6   7 
 1   3 [-1  -3   5]  3   6   7 
 1   3  -1 [-3   5   3]  6   7 
 1   3  -1  -3  [5   3   6]  7 
 1   3  -1  -3   5  [3   6   7]

 引入单调队列: deque<int> dq;

 观察每次窗口移动,我们可以对每次入队的元素评定一个贡献:

 例如 在窗口为[1 3 4]的时刻,如果下一个元素 a[i] 是 5,
 则 [1] 会因为 i - dq.back().num >= k 而被 pop_back()
 则此时窗口剩下[3 4] 
 当前a[i] = 5,如果 [5] 加入队列,则其前面的 [3,4] 将不会有任何贡献 , 因为 5 > 任意[3 4] 
 将任意 <= [5] 的元素pop_back() 最终得到[5]

 则,在求最大值时我们可以有此策略 : while(!dq.empty() && a[i] >= dq.back().val) dq.pop_back();

再例如 在窗口为[1 6 4]的时刻,如果下一个元素 a[i] 是 5,
窗口剩下[6 4] 如果[5]加入队列,则其中的[4]毫无贡献
将任意 <= [5] 的元素pop_front() 最终得到[6 5]

则,在求最大值时我们可以有以下策略 : while(!dq.empty() && a[i] >= dq.front().val) dq.pop_front();

最后 当 i >= k 时即是输出答案的时候 if(i >= k) cout << dq.back().val << " ";


//单调队列求窗口最大值
vector<int> max_deque(vector<int>& a,int k) //数据数组a  窗口大小k
{
    vector<int> ans;
    ans.reserve((int)a.size());
    deque<pair<int,int>> dq;
    for(int i = 1; i < (int)a.size(); i++){
        if(!dq.empty() && i - dq.back().second >= k) dq.pop_back();
        while(!dq.empty() && a[i] >= dq.back().first) dq.pop_back();
        while(!dq.empty() && a[i] >= dq.front().first) dq.pop_front();
        dq.push_front(make_pair(a[i],i));
        if(i >= k) ans.emplace_back(dq.back().first);
    }
    return ans;
}

//单调队列求窗口最小值
vector<int> min_deque(vector<int>& a,int k)
{
    vector<int> ans;
    ans.reserve((int)a.size());
    deque<pair<int,int>> dq;
    for(int i = 1; i < (int)a.size(); i++){
        if(!dq.empty() && i - dq.back().second >= k) dq.pop_back();
        while(!dq.empty() && a[i] <= dq.back().first) dq.pop_back();
        while(!dq.empty() && a[i] <= dq.front().first) dq.pop_front();
        dq.push_front(make_pair(a[i],i));
        if(i >= k) ans.emplace_back(dq.back().first);
    }
    return ans;
}

//单调队列维护区间最小值(DP用)
    int l=1,r=0;
    for(int i=1;i<=n;i++) //枚举当前位置
    {
        while(l <= r && q[l] + m <= i) l++; //去尾 , m为区间长度
        dp[i] = dp[q[l]] + a[i];
        while(l <= r && a[i] < a[q[r]]) r--; //去头
        q[++r] = i; //记录最小元素位置
    }

//单调队列维护区间最大值(DP用)
    int l=1,r=0;
    for(int i=1;i<=n;i++) //枚举当前位置
    {
        while(l <= r && q[l] + m <= i) l++; //去尾 , m为区间长度
        dp[i] = dp[q[l]] + a[i];
        while(l <= r && a[i] > a[q[r]]) r--; //去头
        q[++r] = i; //记录最大元素位置
    }