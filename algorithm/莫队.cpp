#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

// 莫队算法模板
// 适用范围:
// 1. 静态区间询问
// 2. 已知区间 [L, R] 的答案, 能在 O(1) 或均摊 O(1) 时间转移到:
//    [L - 1, R], [L + 1, R], [L, R - 1], [L, R + 1]
// 3. 不支持修改操作(带修莫队请单独写模板)
//
// 使用方式:
// 1. 先把原数组和所有查询读入
// 2. 定义好以下操作:
//    - addLeft(pos)    : 把 a[pos] 加入当前区间左侧
//    - addRight(pos)   : 把 a[pos] 加入当前区间右侧
//    - removeLeft(pos) : 把 a[pos] 从当前区间左侧删除
//    - removeRight(pos): 把 a[pos] 从当前区间右侧删除
//    - getAnswer()     : 返回当前区间答案
// 3. 调用 solve(...) 即可
//
// 说明:
// 1. 若左右加入/删除逻辑完全相同, 也可以把这四个函数写成同一套逻辑
// 2. 下标默认使用 1..n
// 3. 返回答案顺序与加入询问顺序一致

struct MoQuery
{
    int l, r, id, block;

    bool operator < (const MoQuery& t) const
    {
        if(block != t.block) return block < t.block;
        return (block & 1) ? r < t.r : r > t.r;
    }
};

struct Mo
{
    int n, q, block_size;
    vector<MoQuery> query;

    Mo() {}
    Mo(int n_)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        q = 0;
        block_size = max(1, (int)sqrt(n));
        query.clear();
    }

    void addQuery(int l, int r)
    {
        query.push_back({l, r, q++, l / block_size});
    }

    template<class Answer, class AddLeft, class AddRight, class RemoveLeft, class RemoveRight, class GetAnswer>
    vector<Answer> solve(AddLeft addLeft, AddRight addRight, RemoveLeft removeLeft, RemoveRight removeRight, GetAnswer getAnswer)
    {
        sort(query.begin(), query.end());

        vector<Answer> ans(q);
        int L = 1, R = 0;

        for(auto [l, r, id, _] : query)
        {
            while(L > l) addLeft(--L);
            while(R < r) addRight(++R);
            while(L < l) removeLeft(L++);
            while(R > r) removeRight(R--);

            ans[id] = getAnswer();
        }
        return ans;
    }
};

/*
示例1: 区间不同数个数

#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    // 若值域大, 建议先离散化
    vector<int> b(a.begin() + 1, a.end());
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    for(int i = 1; i <= n; i++)
    {
        a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin() + 1;
    }

    Mo mo(n);
    for(int i = 1; i <= q; i++)
    {
        int l, r;
        cin >> l >> r;
        mo.addQuery(l, r);
    }

    vector<int> cnt((int)b.size() + 1, 0);
    int nowAns = 0;

    auto add = [&](int pos)
    {
        if(cnt[a[pos]] == 0) nowAns++;
        cnt[a[pos]]++;
    };

    auto del = [&](int pos)
    {
        cnt[a[pos]]--;
        if(cnt[a[pos]] == 0) nowAns--;
    };

    auto ans = mo.solve<int>(
        add, add, del, del,
        [&]() { return nowAns; }
    );

    for(auto x : ans) cout << x << "\n";
    return 0;
}

------------------------------------------------------------

示例2: 区间内每个值出现次数平方和
即经典模板题:
sum(cnt[x]^2)

维护方法:
加入一个值 v:
now += 2 * cnt[v] + 1
cnt[v]++

删除一个值 v:
cnt[v]--
now -= 2 * cnt[v] + 1

------------------------------------------------------------

复杂度:
1. 排序 O(q log q)
2. 总转移复杂度均摊 O((n + q) * sqrt(n))
3. 若单次 add/remove 为 O(1), 总复杂度通常记作 O(n sqrt(n))

注意:
1. block_size 通常取 sqrt(n)
2. 若值域大, 先离散化
3. 莫队只能处理离线询问
4. 如果题目带修改操作, 需要使用带修莫队
*/