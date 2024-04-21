int fa[maxn];//创建父节点数组

void init(int n)//给父节点初始化，使每个节点的父亲为其自身
{
    for(int i = 1;i <= n;i++) fa[i] = i;
}

int find(int x)//递归查找x元素的祖先,使用压缩路径优化
{
    if(fa[x] == x) return x;//当x与其父亲相同时为祖先，递归结束
    else {
        fa[x] = find(fa[x]);//将父节点设为根节点
        return fa[x];//返回父节点
    }
}

void union(int i,int j)
{
    int i_fa = find(i);//找到i的祖先
    int j_fa = find(j);//找到j的祖先
    fa[j_fa] = i_fa; //让j的祖先变为i的祖先,即将j并入图
}
