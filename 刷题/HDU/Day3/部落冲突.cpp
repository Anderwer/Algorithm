#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

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

void solve()
{
    int n, q;
    cin >> n >> q;

    vector<int> f(n + 1), g(n + 1), p(n + 1);
    DSU d(n + 1);
    for(int i = 1; i <= n; i++)
        f[i] = g[i] = p[i] = i;

    while(q--)
    {
        int op; cin >> op;
        if(op == 1)
        {
            int a, b; cin >> a >> b;
            int u = f[a], v = f[b];
            d.merge(u, v);
            int fa = d.find(u);
            g[fa] = a;
            f[a] = fa;
        }
        else if(op == 2)
        {
            int a, b; cin >> a >> b;
            p[a] = f[b];
        }
        else if(op == 3)
        {
            int a, b; cin >> a >> b;
            int u = f[a], v = f[b];
            swap(g[u], g[v]);
            swap(f[a], f[b]);
        }
        else if(op == 4)
        {
            int a; cin >> a;
            cout << g[d.find(p[a])] << "\n";
        }
    }
}

// 如果没有操作 3, 则是一个普通的 DSU 即可解决, 但现在多了一个连通块之间的交换
// 细想一下, 操作 3 本质上只是改变了两个部落的编号, 我们可以设法建立一个中间映射进行标记
// 设 f[i] : 第 i 个部落对应的 DSU 编号
// 设 g[i] : 第 i 个 DSU 编号对应的部落
// 设 p[i] : 第 i 个人所属部落对应的 DSU 编号

// 执行操作 1 时, a 和 b 合并, 则先用 f[i] 找到 a 和 b 对应的 DSU 编号, 然后再对编号合并然后修改 f[i] 和 g[i] 即可
// 执行操作 2 时, 第 a 个人移动到部落 b 中, 则先找到部落 b 对应的 DSU 编号, 再修改 p[a] 即可
// 执行操作 3 时, 交换部落 a 和部落 b, 我们只需要先获取 a 和 b 对应的 DSU 编号, 然后交换它们的 g[i] 后, 再交换它们的 f[i] 即可
// 执行操作 4 时, 查询第 a 个人所在部落, 则先用 p[i] 找到 DSU 编号, 再用 DSU.find(p[a]) 找到根部落的 DSU 编号, 最后输出 g[DSU.find(p[a])]


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
