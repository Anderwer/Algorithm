#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
int n, m;
vector<int> row;
vector<int> col;
vector<vector<int>> a_bit;
vector<vector<int>> b_bit;

void setrow(int i);

void setcol(int j)
{
    if(col[j] == 1) return;
    col[j] = 1;
    for(int i = 0; i < n; i++)
    {
        if(b_bit[i][j] == 0) setrow(i);
    }
}

void setrow(int i)
{
    if(row[i] == 1) return;
    row[i] = 1;
    for(int j = 0; j < m; j++)
    {
        if(b_bit[i][j] == 1) setcol(j);
    }
}

bool topsort(vector<vector<int>>& e)
{
   vector<int> din(n + m, 0);
    for(int i = 0; i < n + m; i++)
    {
        for(auto x : e[i]) din[x]++;
    }
 
    queue<int> q;
    vector<int> tp;
    for(int i = 0; i < n + m; i++)
    {
        if(din[i] == 0) q.push(i);
    }
    while(!q.empty())
    {
        int x = q.front();
        q.pop();
        tp.push_back(x);
        for(auto y : e[x])
        {
            if(--din[y] == 0) q.push(y);
        }
    }
    return tp.size() == n + m;
}

void solve()
{
    cin >> n >> m;
    
    vector a(n, vector<int>(m));
    vector b(n, vector<int>(m));
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) cin >> a[i][j];
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) cin >> b[i][j];

    a_bit = vector(n, vector<int>(m));
    b_bit = vector(n, vector<int>(m));
    row = vector(n, 0);
    col = vector(m, 0);
    for(int k = 0; k < 30; k++)
    {
        row.assign(n, 0);
        col.assign(m, 0);
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                a_bit[i][j] = a[i][j] >> k & 1;
                b_bit[i][j] = b[i][j] >> k & 1;
            }
        }

        for(int i = 0; i < n; i++)
        {
            if(row[i] == 1) continue;
            for(int j = 0; j < m; j++)
            {
                if(a_bit[i][j] == 1 && b_bit[i][j] == 0)
                {
                    setrow(i);
                    break;
                }
            }
        }
        for(int j = 0; j < m; j++)
        {
            if(col[j] == 1) continue;
            for(int i = 0; i < n; i++)
            {
                if(a_bit[i][j] == 0 && b_bit[i][j] == 1)
                {
                    setcol(j);
                    break;
                }
            }
        }

        vector e(n + m, vector<int>());
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                if(row[i] == 1 && col[j] == 1)
                {
                    if(b_bit[i][j] == 0) e[n + j].push_back(i);
                    else e[i].push_back(n + j);
                }
            }
        }

        if(topsort(e) == false)
        {
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";
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
首先我们规定 row<i> & 0 = 0, 即对一行变 0
            col<j> | 1 = 1, 即对一列变 1

我们把矩阵中的树拆成31位, 每一位都用一个 n x m 的矩阵存着, a_bit[i] 和 b_bit[i] 作为第 i 位的 a,b矩阵
一个数的第k位获取可以用 x >> k & 1 获取
如果对于每一位, 我们都能将 a_bit[i] -> b_bit[i], 则Yes

对于一个 a_bit 二维矩阵, 我们想把它变成 b_bit, 由二进制我们可知, 这两个矩阵里的数非0即1
我们可以通过对 a_bit[i][j] 和 b_bit[i][j] 进行比对, 如果 a_bit[i][j] = 0 而 b_bit[i][j] = 1, 则执行 col<j>, 反之执行 row<i>
同时执行完之后我们要标记一下 row[i] 和 col[j] 为 true

注意到, 对于一个点[i][j], 如果它即执行过row[i], 也执行过col[j], 则要看它最终转化为 0 还是 1
如果最终是 0, 则先执行col[j] 后执行 row[i], 类似二分图处理, 将 点(n + j) 指向点 i
反之, 将点 i 指向点 (n + j)
最后再跑拓扑排序, 如果没有拓扑序则 No

*/