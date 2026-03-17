#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

// Functional Graph
// 适用范围:
// 1. 每个点恰好有一条出边的图
// 2. 需要找环、求点属于哪个环、点到环的距离
// 3. 需要做环上编号、分类讨论树枝与环部分
//
// 约定:
// 1. 点编号默认是 1..n
// 2. to[u] 表示点 u 的出边指向 to[u]
// 3. init(n) 后, 直接设置 to[u] 或使用 setNext(u, v)
// 4. build() 后可使用所有辅助信息

struct FunctionalGraph
{
    int n;                       // 点数
    int loopN;                   // 环的数量

    vector<int> to;              // to[u]: u 指向哪个点
    vector<int> indeg;           // indeg[u]: 入度

    vector<int> loopLen;         // loopLen[id]: 第 id 个环的长度
    vector<int> loopAnyPoint;    // loopAnyPoint[id]: 第 id 个环上的任意一个点

    vector<int> pointLoopId;         // pointLoopId[u]: 点 u 属于哪个环, 若未 build 则无意义
    vector<int> pointIndexInLoop;    // pointIndexInLoop[u]: u 在环上的编号, 若不在环上则为 -1
    vector<int> pointOnLoop;         // pointOnLoop[u]: u 是否在环上
    vector<int> jointPointOnLoop;    // jointPointOnLoop[u]: u 最终接到环上的哪个点
    vector<int> distanceToJointPoint;// distanceToJointPoint[u]: u 到 jointPointOnLoop[u] 的距离

    vector<vector<int>> rev;     // rev[u]: 所有指向 u 的点

    FunctionalGraph() {}
    FunctionalGraph(int n_)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        loopN = 0;

        to.assign(n + 1, 0);
        indeg.assign(n + 1, 0);

        loopLen.clear();
        loopAnyPoint.clear();

        pointLoopId.assign(n + 1, -1);
        pointIndexInLoop.assign(n + 1, -1);
        pointOnLoop.assign(n + 1, 0);
        jointPointOnLoop.assign(n + 1, 0);
        distanceToJointPoint.assign(n + 1, 0);

        rev.assign(n + 1, {});
    }

    void setNext(int u, int v)
    {
        to[u] = v;
    }

    void build()
    {
        buildRev();
        findLoops();
        buildTreeInfo();
    }

    void buildRev()
    {
        fill(indeg.begin(), indeg.end(), 0);
        for(int i = 1; i <= n; i++) rev[i].clear();

        for(int u = 1; u <= n; u++)
        {
            int v = to[u];
            indeg[v]++;
            rev[v].push_back(u);
        }
    }

    void findLoops()
    {
        loopN = 0;
        fill(pointLoopId.begin(), pointLoopId.end(), -1);
        fill(pointIndexInLoop.begin(), pointIndexInLoop.end(), -1);
        fill(pointOnLoop.begin(), pointOnLoop.end(), 0);
        fill(jointPointOnLoop.begin(), jointPointOnLoop.end(), 0);
        fill(distanceToJointPoint.begin(), distanceToJointPoint.end(), 0);
        loopLen.clear();
        loopAnyPoint.clear();

        vector<int> deg = indeg;
        queue<int> q;
        vector<int> onCycle(n + 1, 1);

        for(int i = 1; i <= n; i++)
        {
            if(deg[i] == 0) q.push(i);
        }

        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            onCycle[u] = 0;

            int v = to[u];
            if(--deg[v] == 0) q.push(v);
        }

        vector<int> vis(n + 1, 0);
        for(int i = 1; i <= n; i++)
        {
            if(!onCycle[i] || vis[i]) continue;

            int cur = i;
            vector<int> cyc;
            while(!vis[cur])
            {
                vis[cur] = 1;
                cyc.push_back(cur);
                cur = to[cur];
            }

            int id = loopN++;
            loopLen.push_back((int)cyc.size());
            loopAnyPoint.push_back(cyc[0]);

            for(int j = 0; j < (int)cyc.size(); j++)
            {
                int u = cyc[j];
                pointLoopId[u] = id;
                pointIndexInLoop[u] = j;
                pointOnLoop[u] = 1;
                jointPointOnLoop[u] = u;
                distanceToJointPoint[u] = 0;
            }
        }
    }

    void dfsTree(int u, int rootOnLoop, int dist, int loopId)
    {
        pointLoopId[u] = loopId;
        pointOnLoop[u] = 0;
        pointIndexInLoop[u] = -1;
        jointPointOnLoop[u] = rootOnLoop;
        distanceToJointPoint[u] = dist;

        for(auto v : rev[u])
        {
            if(pointOnLoop[v]) continue;
            if(v == to[u]) continue;
            dfsTree(v, rootOnLoop, dist + 1, loopId);
        }
    }

    void buildTreeInfo()
    {
        for(int id = 0; id < loopN; id++)
        {
            int start = loopAnyPoint[id];
            int cur = start;
            do
            {
                for(auto v : rev[cur])
                {
                    if(pointOnLoop[v]) continue;
                    dfsTree(v, cur, 1, id);
                }
                cur = to[cur];
            } while(cur != start);
        }
    }

    int nextOnLoop(int u, int step = 1) const
    {
        // 要求 u 在环上
        int id = pointLoopId[u];
        int pos = pointIndexInLoop[u];
        int len = loopLen[id];
        int k = ((step % len) + len) % len;

        int cur = u;
        while(k--)
        {
            cur = to[cur];
        }
        return cur;
    }

    int distOnLoop(int u, int v) const
    {
        // 有向环上从 u 走到 v 的步数, 要求 u 和 v 在同一个环上
        int id = pointLoopId[u];
        int len = loopLen[id];
        int pu = pointIndexInLoop[u];
        int pv = pointIndexInLoop[v];
        return (pv - pu + len) % len;
    }
};

/*
使用示例:

int n;
cin >> n;
FunctionalGraph fg(n);
for(int i = 1; i <= n; i++)
{
    int v;
    cin >> v;
    fg.setNext(i, v);
}
fg.build();

可用信息:
1. fg.loopN
   环的数量

2. fg.loopLen[id]
   第 id 个环的长度

3. fg.pointOnLoop[u]
   点 u 是否在环上

4. fg.pointLoopId[u]
   点 u 属于哪个环

5. fg.pointIndexInLoop[u]
   若 u 在环上, 则表示它在环上的编号

6. fg.jointPointOnLoop[u]
   若 u 不在环上, 则表示它最终走到环上的哪个点

7. fg.distanceToJointPoint[u]
   点 u 到其连接环点的距离

8. fg.distOnLoop(u, v)
   若 u, v 在同一环上, 返回从 u 沿出边方向走到 v 的步数
*/