线段树是一种基于分治思想的二叉树,其特点与区间L,R有关
给定一个[1,R]的数组,将它划为线段树
有特点: 叶子结点L == R, 非叶子结点 左子树为[1,(L+R)/2],右子树为[(L+R)/2 + 1, R]

1.线段树的存储方式
    对于区间最大,最小值查询问题,线段树的每个节点包含三个域: L,R,mx 其中L,R代表区间左右端点,mx代表[L,R]之间的最大值
    由于线段树除了最后一层,其余都是满二叉树,因此可以用顺序存储,用一个数组tree[]存储结点 (当前结点为k,则其左结点为2k,右节点为2k + 1)
    注意,n个元素 tree[] 一般开 4n 大小

2.创建线段树
    递归建树
    (1).如果是叶子结点L == R, 则节点的最值就是对应数组的元素值
    (2).如果是非叶子结点,递归创建左子树和右子树
    (3).结点的区间最值等于该节点的左右子树的最大值

携带区间信息建树:

#define lc k<<1
#define rc k<<1|1
const int N = 1e4 + 10;
struct node{
    int L,R,mx;
}tree[N * 4];

void build(int k, int L, int R) //k 为结点存储下标
{
    tree[k].L = L;
    tree[k].R = R;
    if(L == R){ //到达叶子结点
        tree[k].mx = a[L];
        return;
    }
    int mid = (L + R) / 2;
    build(lc, L, mid);
    build(rc, mid + 1, R);
    tree[k].mx = max(tree[lc].mx, tree[rc].mx);
}

3.点更新:
    修改一个元素的值,将a[i] 修改成 v
    (1).如果是叶子结点,满足 L == R 且 L == i,则修改该点最值为v
    (2).如果是非叶子结点,判断是在左子树更新还是右子树更新
    (3).返回时更新节点最值

void update(int k, int i, int v) //点更新,将a[i]修改成v
{
    if(tree[k].L == tree[k].R && tree[k].L == i){
        tree[k].mx = v;
        return;
    }
    int mid = (tree[k].L + tree[k].R) / 2;
    if(i <= mid) update(lc, i, v); //判断a[i]在左子树还是右子树
    else update(rc, i, v);
    tree[k].mx = max(tree[lc].mx, tree[rc].mx);
}

4.区间查询(区间覆盖法,区间相等法):
    查询一个[L,R]区间的最值
    (1).若节点所在的区间被查询区间[L,R]覆盖,则返回该节点的最值
    (2).判断是在左子树中查询,还是在右子树中查询
    (3).返回最值

区间覆盖法:
int query1(int k, int L, int R)
{
    if(L <= tree[k].L && R >= tree[k].R) return tree[k].mx;
    int mid = (tree[k].L + tree[k].R) / 2;
    int Max = -(0x7f7f7f7f);
    if(L <= mid) Max = max(Max, query1(lc, L, R));
    if(R > mid) Max = max(Max, query1(rc, L, R));
    return Max;
}

区间相等法:
int query2(int k, int L, int R)
{
    if(L == tree[k].L && R == tree[k].R) return tree[k].mx;
    int mid = (tree[k].L + tree[k].R) / 2;
    if(R <= mid) return query2(lc, L, R);
    else if(L > mid) return query2(rc, L, R);
    else return max(query2(lc, L, mid), query2(rc, mid + 1, R));
}

5.区间修改(以线段树求区间和为例):

const int N = 1e4 + 10;
struct node{
    int L,R,lazy;
    long long sum;
}tree[N * 4];

void build(int k, int L, int R)
{
    tree[k].L = L;
    tree[k].R = R;
    if(L == R) {
        tree[k].sum = a[i];
        return;
    }
    int mid = (L + R) / 2;
    build(lc, L, mid);
    build(rc, mid + 1, R);
    tree[k].sum = tree[lc].sum + tree[rc].sum;
}

void pushdown(int k) //下传懒标记
{
    if(tree[k].lazy){
        tree[lc].sum += (tree[lc].R - tree[lc].L + 1) * tree[k].lazy;
        tree[rc].sum += (tree[rc].R - tree[rc].L + 1) * tree[k].lazy;
        tree[lc].lazy += tree[k].lazy;
        tree[rc].lazy += tree[k].lazy;
        tree[k].lazy = 0;
    }
}

void update(int k, int L, int R, int x)
{
    if(L <= tree[k].L && R >= tree[k].R){
        tree[k].sum += (tree[k].R - tree[k].L + 1) * x;
        tree[k].lazy += x;
        return;
    }
    int mid = (tree[k].L + tree[k].R) / 2;
    pushdown(k);
    if(L <= mid) update(lc, L, R, x);
    if(R > mid) update(rc, L, R, x);
    tree[k].sum = tree[lc].sum + tree[rc].sum;
}

long long query(int k, int L, int R)
{
    if(L <= tree[k].L && R >= tree[k].R) return tree[k].sum;
    int mid = (tree[k].L + tree[k].R) / 2;
    pushdown(k);
    long long sum = 0;
    if(L <= mid) sum += query(lc, L, R);
    if(R > mid) sum += query(rc, L, R);
    return sum;
}