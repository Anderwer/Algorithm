双向广度优先搜索(DBFS) 适用于起点和终点都已知的情况

参考 :  P1379 八数码难题
代码框架:
初始化两个队列 q[0] 和 q[1] ,起点和终点分别加入到两个队列中
初始化两个map  mp[0] 和 mp[1], key字符串表示的状态, value是走到当前状态的步数

while(!q[0].empty() && !q[1].empty())
{
    if(q[0].size() < q[1].size()) expand(0);
    else expand(1);
}

while(!q[0].size()) expand(0);
while(!q[1].size()) expend(1);

这里的expand() 是进行BFS操作
其中 expand()函数参考实现:

void expand(int i) 参数 i 代表对哪个队列进行操作
{
    string h = q[i].front(); //取出队头
    q.pop();
    if(mp[1 - i][h]) {
        ans = mp[1-i][h] + step;
        return;
    }
    遍历此时的四个方向,如果没有状态出现在mp[i]中,则加入mp[i]和q[i];
}
