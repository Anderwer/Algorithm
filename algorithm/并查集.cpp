const int maxn = 100010;

int fa[maxn]; //fa[]记录每个元素由谁代表
int sz[maxn]; //sz[]记录每个集合元素个数
int depth[maxn]; //depth[]记录每个集合的树深度

void init(int n)
{
    for(int i = 1; i <= n; i++)
    {
        fa[i] = i;
        sz[i] = depth[i] = 1;
    }
}

int find(int x)
{
    if(x == fa[x]) return x;
    fa[x] = find(fa[x]);
    return fa[x];
}

void unionn(int x, int y) //普通合并
{
    int fx = find(x), fy = find(y);
    if(fx == fy) return;
    fa[fx] = fy;
}

void Union_size(int x, int y) //启发式合并
{
    int fx = find(x), fy = find(y);
    if(fx == fy) return;
    if(sz[fx] > sz[fy]) swap(fx, fy);
    fa[fx] = fy;
    sz[fy] += sz[fx];
}

void Union_depth(int x, int y) //按深度合并
{
    int fx = find(x), fy = find(y);
    if(fx == fy) return;
    if(depth[fx] > depth[fy]) swap(fx, fy);
    fa[fx] = fy;
    if(depth[fx] == depth[fy]) depth[fy]++;
}





struct DSU
{
    vector<int> f, siz;

    DSU() {}
    DSU(int n)
    {
        init(n);
    }

    void init(int n)
    {
        f.resize(n);
        iota(f.begin(), f.end(), 0);
        siz.assign(n, 1);
    }

    int find(int x)
    {
        while(x != f[x]) x = f[x] = f[f[x]];
        return x;
    }

    bool same(int x, int y)
    {
        return find(x) == find(y);
    }

    bool merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        if(x == y) return false;
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }

    int size(int x)
    {
        return siz[find(x)];
    }
};