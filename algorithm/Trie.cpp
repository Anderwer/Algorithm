
// 普通字典树
const int N = 100010;
const int charsize = 26;
int Trie[N + 1][charsize];
bool isend[N + 1];
int root = 0, cnt = 0;

void insert(string& s)
{
    int cur = 0;
    for(auto c : s)
    {
        int x = c - 'a';
        if(!Trie[cur][x]) Trie[cur][x] = ++cnt;
        cur = Trie[cur][x];
    }
    isend[cur] = true;
}

bool search(string& s)
{
    int cur = 0;
    for(auto c : s)
    {
        int x = c - 'a';
        if(!Trie[cur][x]) return false;
        cur = Trie[cur][x];
    }
    return isend[cur];
}


// 01 Trie
struct T
{
    vector<array<int, 2>> Trie;
    int cnt;

    T() {}
    T(int n)
    {
        init(n);
    }

    void init(int n)
    {
        Trie = vector<array<int, 2>>(n * 32 + 10);
        cnt = 0;
    }

    void insert(int x)
    {
        int cur = 0;
        for(int i = 30; i >= 0; i--)
        {
            int j = (x >> i) & 1;
            if(!Trie[cur][j]) Trie[cur][j] = ++cnt;
            cur = Trie[cur][j];
        }
    }

    int query(int x)
    {
        int cur = 0, res = 0;
        for(int i = 30; i >= 0; i--)
        {
            int j = (x >> i) & 1;
            if(Trie[cur][!j])
            {
                res += (1 << i);
                cur = Trie[cur][!j];
            }
            else cur = Trie[cur][j];
        }
        return res;
    }
};

// 可持久化01 Trie
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