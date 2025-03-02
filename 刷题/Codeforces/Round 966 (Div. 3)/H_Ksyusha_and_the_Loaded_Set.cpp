#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

template<class Node>
struct SegmentTree
{
    #define lc u << 1
    #define rc u << 1 | 1
    const int n, N;
    vector<Node> tree;

    SegmentTree(): n(0) {}
    SegmentTree(int n_): n(n_), N(n * 4 + 10)
    {
        tree.reserve(N);
        tree.resize(N);
        build(1, 1, n);
    }

    void build(int u, int l, int r)
    {
        tree[u].l = l, tree[u].r = r;
        if(l == r)
        {
            tree[u] = {l, r, 1, 1, 1};
            return;
        }
        i64 mid = (l + r) >> 1;
        build(lc, l, mid);
        build(rc, mid + 1, r);  
        pushup(tree[u], tree[lc], tree[rc]);
    }

    void pushup(Node& U, Node& L, Node& R) //上传
    {
        U.l = L.l, U.r = R.r;

        if(L.lsum == L.r - L.l + 1) U.lsum = L.lsum + R.lsum; //左儿子区间全是 0
        else U.lsum = L.lsum;

        if(R.rsum == R.r - R.l + 1) U.rsum = L.rsum + R.rsum; //右儿子区间全是 0
        else U.rsum = R.rsum;

        U.Maxsum = max({L.Maxsum, R.Maxsum, L.rsum + R.lsum});
    }

    void modify(int u, int pos)
    {
        if(tree[u].l >= pos && tree[u].r <= pos)
        {
            tree[u].Maxsum = 1 - tree[u].Maxsum;
            tree[u].lsum = tree[u].rsum = tree[u].Maxsum;
            return;
        }
        int mid = (tree[u].l + tree[u].r) >> 1;
        if(pos <= mid) modify(lc, pos);
        else modify(rc, pos);
        pushup(tree[u], tree[lc], tree[rc]);
    }

    int query(int u, int k) //区查
    {
        if(tree[u].l == tree[u].r) return tree[u].l;

        if(tree[lc].Maxsum >= k) return query(lc, k); //线段树二分, 先找左

        if(tree[lc].rsum + tree[rc].lsum >= k) return tree[lc].r - tree[lc].rsum + 1;

        return query(rc, k);
    }

};

struct Node
{
    i64 l, r;
    i64 lsum, rsum, Maxsum;
};

const int N = 2e6;
SegmentTree<Node> T(N);

void solve()
{
    int n;
    cin >> n;
    set<int> s;
    for(int i = 1; i <= n; i++)
    {
        int x; cin >> x;
        s.insert(x);
        T.modify(1, x);
    }

    int q; cin >> q;
    while(q--)
    {
        char c;
        int x;
        cin >> c >> x;
        if(c == '-')
        {
            s.erase(x);
            T.modify(1, x);
        }
        else if(c == '+')
        {
            s.insert(x);
            T.modify(1, x);
        }
        else if(c == '?')
        {
            if(x > T.tree[1].Maxsum) cout << N - T.tree[1].rsum + 1 << " ";
            else cout << T.query(1, x) << " ";
        }
    }
    cout << "\n";

    for(auto v : s) T.modify(1, v);
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
对于查询, 第 k 负载也就是寻找一个最小区间左端点使得区间 [d, d + k - 1] 中的所有数都不在集合S中, 这个区间长度为 k
因此, 对于集合S = {x1, x2, x3, ..., xn}, 我们可以维护相邻两个点的区间长度 x[i + 1] - x[i]
从左往右找第一个 x[i + 1] - x[i] > k 的区间, 此时答案为 x[i] + 1

考虑线段树, 对于集合中出现的数, 我们可以在线段树中标记为 1, 那么两个 1 之间的 0 的个数就是长度, 那么只需要维护这个区间最大的 0 的个数即可
本身区间最长连续0之间不可以进行区间加法操作, 违背线段树基本的运算, 但是容易想到两个区间合并产生的最值变化，主要由Lson的右端连续0长度加上Rson的左端连续0长度引起
因此我们可以考虑维护一个区间的左端连续0个数和右端连续0个数.
查询的时候, 由于要找最左边的, 所以先从左儿子找起, 找到一个节点时, 如果 Lson.rsum + Rson.lsum >= k, 则返回 Lson.r - Lson.rsum + 1


*/