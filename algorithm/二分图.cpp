判断一个图是否是二分图 : 染色法

const int N = 10005;
vector<int> g[N];
int n, m, color[N];

bool dfs(int x)
{
    for(auto& y : g[x])
    {
        if(color[y] == 0)
        {
            color[y] = 3 - color[x];
            if(dfs(y) == false) return false;
        }
        else
        {
            if(color[x] == color[y]) return false;
        }
    }
    return true;
}

bool check()
{
    memset(color, 0, sizeof(color));
    for(int i = 1; i <= n; i++)
    {
        if(color[i] == 0)
        {
            color[i] = 1;
            if(dfs(i) == false) return false;
        }
    }
    return true;
}


二分图最大匹配 :

增广路算法 : O(nm)

const int N = 10005;
vector<int> g[N]; //存左边到右边的边
int n, m, n1, n2, v[N]; //n1为左边点的数量, n2为右边点的数量, v[]表示右边第i个点与左边第v[i]个点匹配了,如果没匹配则v[i] = 0
bool vis[N];

bool find(int x)
{
    vis[x] = true;
    for(auto& y : g[x])
    {
        if(!v[y] || (!vis[v[y]] && find(v[y]))) // !v[y] <==> 右边的点未被匹配
        {                                       // 如果右边第y个点被匹配过了, v[y] 存了左边谁匹配的右边y, 那就从左边v[y]作为新的起点找增广路
            v[y] = x;
            return true;
        }
    }
    return false;
}

int match()
{
    int ans = 0;
    memset(v, 0, sizeof(v));
    for(int i = 1; i <= n1; i++)
    {
        memset(vis, false, sizeof(vis));
        if(find(i)) ans++;
    }
    return ans;
}


二分图结论 :
(1).最小点覆盖：选最少的点，满足每条边至少有一个端点被选。
    二分图中, 最小点覆盖 = 最大匹配

(2).最大独立集：选最多的点，满足两两之间没有边相连。
    二分图中, 最大独立集 = n - 最小点覆盖 = n - 最大匹配

(3).遇到很多有向无环图问题可以考虑拆点, 把一个点拆成出去和进来, 出去的统一放在左边, 进来的统一放在右边, 可能可以转化成二分图问题



增广路算法建图一般有如下几种情况 :

(1).行列匹配法 : 这类题目一般是判断一行或一列有无点存在，一般用于处理与棋盘有关的题目，这些题目有一个基本上相同的特点，就是求最少用几条直线能覆盖棋盘上的点。

(2).黑白染色法 : 黑白染色法是以一个点为黑点，与它相邻的点定为白点，并与之连边。同样用来解决覆盖问题

(3).反建法 : 通过题目所给的条件，从反面出发，建边，计算最大匹配，输出 n - 最大匹配数

(4).拆点法 : 主要用来求最小路径覆盖问题，与之相关的有一个定理：最小路径覆盖数 = 点数 - 最大匹配数

(5).一行变多行，一列变多列

(6).混合法

