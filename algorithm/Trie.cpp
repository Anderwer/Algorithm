#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

// 普通字典树
struct Trie
{
    static const int charsize = 26;

    vector<array<int, charsize>> tr;
    vector<int> isend;
    int cnt;

    Trie() {}
    Trie(int n)
    {
        init(n);
    }

    void init(int n)
    {
        tr.assign(n + 1, array<int, charsize>{});
        isend.assign(n + 1, 0);
        cnt = 0;
    }

    void insert(const string& s)
    {
        int cur = 0;
        for(auto c : s)
        {
            int x = c - 'a';
            if(!tr[cur][x]) tr[cur][x] = ++cnt;
            cur = tr[cur][x];
        }
        isend[cur] = 1;
    }

    bool search(const string& s)
    {
        int cur = 0;
        for(auto c : s)
        {
            int x = c - 'a';
            if(!tr[cur][x]) return false;
            cur = tr[cur][x];
        }
        return isend[cur];
    }

    bool startsWith(const string& s)
    {
        int cur = 0;
        for(auto c : s)
        {
            int x = c - 'a';
            if(!tr[cur][x]) return false;
            cur = tr[cur][x];
        }
        return true;
    }
};


// 01 Trie
struct BinaryTrie
{
    vector<array<int, 2>> tr;
    int cnt;

    BinaryTrie() {}
    BinaryTrie(int n)
    {
        init(n);
    }

    void init(int n)
    {
        tr.assign(n * 32 + 10, array<int, 2>{});
        cnt = 0;
    }

    void insert(int x)
    {
        int cur = 0;
        for(int i = 30; i >= 0; i--)
        {
            int j = (x >> i) & 1;
            if(!tr[cur][j]) tr[cur][j] = ++cnt;
            cur = tr[cur][j];
        }
    }

    int queryMaxXor(int x)
    {
        int cur = 0, res = 0;
        for(int i = 30; i >= 0; i--)
        {
            int j = (x >> i) & 1;
            if(tr[cur][!j])
            {
                res |= (1 << i);
                cur = tr[cur][!j];
            }
            else cur = tr[cur][j];
        }
        return res;
    }

    int queryMinXor(int x)
    {
        int cur = 0, res = 0;
        for(int i = 30; i >= 0; i--)
        {
            int j = (x >> i) & 1;
            if(tr[cur][j]) cur = tr[cur][j];
            else
            {
                res |= (1 << i);
                cur = tr[cur][!j];
            }
        }
        return res;
    }
};


// 可持久化01 Trie
struct PersistentBinaryTrie
{
    vector<array<int, 2>> tr;
    vector<int> root, sz;
    int cnt, idx;

    PersistentBinaryTrie() {}
    PersistentBinaryTrie(int n)
    {
        init(n);
    }

    void init(int n)
    {
        tr.assign(n * 32 + 10, array<int, 2>{});
        root.assign(n + 1, 0);
        sz.assign(n * 32 + 10, 0);
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
            tr[cur] = tr[pre];
            tr[cur][j] = ++cnt;
            pre = tr[pre][j];
            cur = tr[cur][j];
            sz[cur] = sz[pre] + 1;
        }
    }

    int queryMaxXor(int lRoot, int rRoot, int x)
    {
        int res = 0;
        for(int i = 30; i >= 0; i--)
        {
            int j = (x >> i) & 1;
            if(sz[tr[rRoot][!j]] > sz[tr[lRoot][!j]])
            {
                lRoot = tr[lRoot][!j];
                rRoot = tr[rRoot][!j];
                res |= (1 << i);
            }
            else
            {
                lRoot = tr[lRoot][j];
                rRoot = tr[rRoot][j];
            }
        }
        return res;
    }

    int queryMaxXor(int l, int r, int x)
    {
        return queryMaxXor(root[l - 1], root[r], x);
    }
};