#include<bits/stdc++.h>
using namespace std;
const int N = 500005;
struct node
{
    int v;//指向下一个点
    int w;//边权
    bool operator < (const node &b)const//重载 < 
    {
        return w > b.w;
    }
}now,tmp;
int n,m,s;
vector<node> MAP[N];//图
int d[N];//最短路数组
bool vis[N];//标记数组
void dijkstra(int s,int e)//从s到e
{
    d[s] = 0;
    now.v = s;
    now.w = 0;
    priority_queue<node> q;
    q.push(now);
    while(!q.empty())//BFS
    {
        now = q.top();
        q.pop();
        if(vis[now.v] == true) continue;
        vis[now.v] = true;
        int len = MAP[now.v].size();
        for(int i = 0; i < len; i++)//遍历一个点所连的后面几个点
        {
            tmp = MAP[now.v][i];
            if(d[now.v] + tmp.w < d[tmp.v])
            {
                d[tmp.v] = d[now.v] + tmp.w;
                q.push((node){ tmp.v, d[tmp.v]});
            }
        }
    }
}
int main()
{
    	cin >> n >> m >> s;
        for(int i = 1 ; i <= n; i++)
        {
            MAP[i].clear();
            d[i]= 2147483647;
            vis[i] = false;
        }
        while(m--)
        {
            int u,v,w;
            cin >> u >> v >> w;
            MAP[u].push_back((node){v,w});
           // MAP[v].push_back((node){u,w});如果是有向边，这条不需要
        }
        dijkstra(s,n);//从s到n的最短路
        for(int i = 1; i <= n; i++) cout << d[i] << " ";
    return 0;
}