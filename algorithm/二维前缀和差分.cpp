
int n, m;
vector<vector<int>> pre(n + 2, vector<int>(m + 2, 0));
vector<vector<int>> d(n + 2, vector<int>(m + 2, 0));

void mark(int xa, int ya, int xb, int yb, int c)
{
    d[xa][ya] +=c;
    d[xb + 1][yb + 1] += c;
    d[xb + 1][ya] -= c;
    d[xa][yb + 1] -= c;
}

void init()
{
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++) cin >> a[i][j];

    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++) mark(i, j, i, j, a[i][j]);
}

void add()
{
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++) a[i][j] = a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1] + d[i][j];
}

