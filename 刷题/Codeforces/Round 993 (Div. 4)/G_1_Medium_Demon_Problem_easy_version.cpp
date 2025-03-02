#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

struct FunctionalGraph
{
    int loopN; //环的个数
    vector<int> loopLen; //loopLen[i] : 第 i 个环的节点个数
    vector<int> loopAnyPoint; //loopAnyPoint[i] : 第 i 个环上任意一个节点
    vector<int> pointLoopId; //pointLoopId[i] : 第 i 个节点属于哪个环
    vector<int> pointIndexInLoop; //pointIndexInLoop[i] : 第 i 个节点在环内的下标, 如果 -1 则不在环内
    vector<bool> pointOnLoop; //pointOnLoop[i] : 第 i 个节点是否在环上
    vector<int> jointPointOnLoop; //jointPointOnLoop[i] : 第 i 个节点和环相连接的点是哪个点
    vector<int> distanceToJointPoint; //distanceToJointPoint[i] : 第 i 个节点和环相连接的点之间的距离
    int pointN; //图中节点的数量

    FunctionalGraph(vector<int>& d)
    {
        pointN = d.size();
        loopN = 0;
        loopLen.assign(pointN, 0);
        loopAnyPoint.assign(pointN, 0);
        pointLoopId.assign(pointN, 0);
        pointIndexInLoop.assign(pointN, -1);
        pointOnLoop.assign(pointN, false);
        jointPointOnLoop.assign(pointN, 0);
        distanceToJointPoint.assign(pointN, 0);
        findLoop(d);
    }

    void findLoop(vector<int>& d)
    {
        int n = d.size();
        pointLoopId.assign(pointN, -1);
        loopN = 0;
        vector<int> t(n, 0);
        int tn = 0;
        for(int i = 0; i < n; i++)
        {
            if(pointLoopId[i] != -1) continue;
            tn = 0;
            int cur = i;
            while(pointLoopId[cur] == -1)
            {
                pointLoopId[cur] = loopN;
                t[tn++] = cur;
                cur = d[cur];
            }
            if(pointLoopId[cur] < loopN)
            {
                int loopId = pointLoopId[cur];
                int jointPoint = jointPointOnLoop[cur];
                for(int j = 0; j < tn; j++)
                {
                    pointLoopId[t[j]] = loopId;
                    jointPointOnLoop[t[j]] = jointPoint;
                    distanceToJointPoint[t[j]] = tn - j + distanceToJointPoint[cur];
                }
            }
            else
            {
                int loopId = loopN;
                loopAnyPoint[loopId] = cur;
                for(int j = 0; j < tn; j++)
                {
                    if(t[j] == cur)
                    {
                        loopLen[loopId] = tn - j;
                        break;
                    }
                }
                int idx = 0;
                for(int j = 0; j < tn; j++)
                {
                    if(tn - j <= loopLen[loopId])
                    {
                        pointOnLoop[t[j]] = true;
                        jointPointOnLoop[t[j]] = t[j];
                        pointIndexInLoop[t[j]] = idx++;
                    }
                    else
                    {
                        jointPointOnLoop[t[j]] = cur;
                        distanceToJointPoint[t[j]] = tn - loopLen[loopId] - j;
                    }
                }
                loopN++;
            }
        }
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
        a[i]--; //下标从0开始
    }

    FunctionalGraph fg(a);
    int ans = 0;
    for(int i = 0; i < n; i++) ans = max(ans, fg.distanceToJointPoint[i] + 2);
    cout << ans << "\n";
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
