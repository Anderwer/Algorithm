#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

struct T
{
    vector<array<int, 2>> Trie;
    vector<int> root, sz;
    int cnt, idx;

    T() {}
    T(int n)
    {
        init(n);
    }

    void init(int n)
    {
        Trie = vector<array<int, 2>>(n * 32 + 10);
        root = vector<int>(n + 1);
        sz = vector<int>(n * 32 + 10);
        cnt = idx = 0;
    }

    void insert(int x)
    {
        root[++idx] = ++cnt;
        int pre = root[idx - 1];
        int cur = root[idx];
        for(int i = 30; i >= 0; i--)
        {
            int j = (x >> i) & 1;
            Trie[cur] = Trie[pre];
            Trie[cur][j] = ++cnt;
            pre = Trie[pre][j];
            cur = Trie[cur][j];
            sz[cur] = sz[pre] + 1;
        }
    }

    int query(int pre, int cur, int x) // 查询区间[L, R] 和 x 异或最大值时, query(root[L - 1], root[R], x)
    {
        int res = 0;
        for(int i = 30; i >= 0; i--)
        {
            int j = (x >> i) & 1;
            if(sz[Trie[cur][!j]] > sz[Trie[pre][!j]])
            {
                pre = Trie[pre][!j];
                cur = Trie[cur][!j];
                res ^= (1 << i);
            }
            else
            {
                pre = Trie[pre][j];
                cur = Trie[cur][j];
            }
        }
        return res;
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;
    T trie(n + 1);
    for(int i = 1; i <= n; i++)
    {
        int x; cin >> x;
        trie.insert(x);
    }

    while(q--)
    {
        int L, R, x;
        cin >> L >> R >> x;
        cout << trie.query(trie.root[L - 1], trie.root[R], x) << "\n";
    }
}

// 手玩一下式子发现, (a | x) ^ (a & x) = a ^ x
// 因此, 题目要求每次询问给定一个 [L, R] 和 x, 找到最大的 i ∈ [L, R] 使得 a[i] ^ x 最大
// 想到求异或最大值可以用 01Trie 解决, 但这是在区间中求
// 有一种数据结构 可持久化01Trie 即可解决这类问题

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
