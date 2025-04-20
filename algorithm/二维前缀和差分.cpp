
int a[N][N], pre[N][N];
void init() //构造差分数组
{
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++) 
            pre[i][j] = a[i][j] - a[i - 1][j] - a[i][j - 1] + a[i - 1][j - 1];
}
void mark(int xa, int ya, int xb, int yb, int val)
{
    pre[xa][ya] += c;
    pre[xb + 1][yb + 1] += c;
    pre[xa][yb + 1] -= c;
    pre[xb + 1][ya] -= c;
}
void add() //差分标记完再前缀和
{
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            pre[i][j] = pre[i][j] + pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1];
}