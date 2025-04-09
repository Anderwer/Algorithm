#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const int N = 1e5 + 10;
vector<int> g[N], h[N];
int id[10][10][10][10];
int f[N], cnt[N];
int cur = 0;

void add(int v, int xa, int xb, int ya, int yb)
{
    int u = id[ya][yb][xa][xb]; // 后手变先手
    g[u].push_back(v); // g[i] 存从末态到初态
    h[v].push_back(u); // h[i] 存初态到末态
}

void init()
{
    queue<int> q;
    for(int xa = 0; xa < 10; xa++)
        for(int xb = 0; xb < 10; xb++)
            for(int ya = 0; ya < 10; ya++)
                for(int yb = 0; yb < 10; yb++)
                {
                    id[xa][xb][ya][yb] = ++cur;
                    if(xa == 0 && xb == 0) f[cur] = 1, q.push(cur); //先手必胜
                    else if(ya == 0 && yb == 0) f[cur] = 2, q.push(cur); //先手必败
                }

    for(int xa = 0; xa < 10; xa++)  
        for(int xb = 0; xb < 10; xb++)
            for(int ya = 0; ya < 10; ya++)
                for(int yb = 0; yb < 10; yb++)
                {
                    int v = id[xa][xb][ya][yb]; // 枚举当前状态，下一个状态连向当前状态
                    if(xa && ya) add(v, (xa + ya) % 10, xb, ya, yb);
                    if(xa && yb) add(v, (xa + yb) % 10, xb, ya, yb);
                    if(xb && ya) add(v, xa, (xb + ya) % 10, ya, yb);
                    if(xb && yb) add(v, xa, (xb + yb) % 10, ya, yb);
                }
    
    while(!q.empty())
    {
        int now = q.front();
        q.pop();
        if(f[now] == 1)
        {
            for(auto v : g[now]) // 当前是必胜态，需要统计上一个状态是否连的都是必胜态
            {
                if(f[v] == 0)
                {
                    cnt[v]++;
                    if(cnt[v] == h[v].size())//如果一个状态连的都是必胜态，则它为必败态
                    {
                        f[v] = 2;
                        q.push(v);
                    }
                }
            }
        }
        else 
        {
            for(auto v : g[now]) // 当前是必败态，与之相连的上一个状态都是必胜态
            {
                if(f[v] == 0)
                {
                    f[v] = 1;
                    q.push(v);
                }
            }
        }
    }
}

void solve()
{
    int xa, xb, ya, yb;
    cin >> xa >> xb >> ya >> yb;
    cout << f[id[xa][xb][ya][yb]] << "\n";
}

// 正难则反，考虑从结束态往前推，由于博弈论的各个状态相当于一张有向图，可以考虑建图
// 设 f[xa][xb][ya][yb] 表示先手状态为 xa，xb， 后手状态为 ya，yb时是否为必胜态
// 初始时 f[0][0][all][all] = 1, f[all][all][0][0] = 2, 注意修改 f[0][0][0][0] = 1
// 将所有状态进行编号，然后建图，对于当前状态 {xa, xb, ya, yb} 考虑转移
// 可以转移到 {(xa + ya) % 10, xb} {(xa + yb) % 10, xb} {xa, (xb + ya) % 10} {xa, (xb + yb) % 10}

// 如果当前是必败态，由于双方足够聪明，则所有与它相连的状态都是必胜态
// 如果当前是必胜态，则让与它相连的所有cnt[v] + 1, 当一个节点的 cnt[v] == 入度 时，它为必败态


int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    cin >> t;
    init();
    while(t--)
    {
        solve();
    }
    return 0;
}
