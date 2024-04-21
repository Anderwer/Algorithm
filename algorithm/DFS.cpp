DFS模板

void dfs(int step)
{
    if(到达目的地)
    {
        输出解;
        返回;
    }
    合理的剪枝操作
    for(int i=1;i<=枚举数;i++)
    {
        if(满足条件)
        {
            更新状态位;
            dfs(step+1);
            恢复状态位;
        }
    }
}