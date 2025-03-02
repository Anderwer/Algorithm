树状数组是一种支持 单点修改 和 区间查询 的，代码量小的数据结构。

注意:1.树状数组必须下标以1开始
     2.区间修改&单点查询时需要用差分思想: 用树状数组维护一个差分数组的前缀和
     3.区间修改&区间查询时需要用差分思想: 用树状数组维护两个差分数组的前缀和


//单点修改&区间查询

const int N = 2000010;
int tree[N];
int n,m;
inline int lowbit(int x) 
{
    return x & -x;
}
void add(int index, int x) //增
{
    for(int i = index; i <= n; i += lowbit(i)){
        tree[index] += x;
    }
}
int sum(int index) //区间和
{
    int ans = 0;
    for(int i = index; i ; i -= lowbit(i)){
        ans += tree[index];
    }
    return ans;
}

void solve()
{
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        add(i,x);
    }
    while(m--){
        int op,x,k,y;
        cin >> op;
        if(op == 1) { //单点修改
            cin >> x >> k;
            add(x,k);
        }
        else if(op == 2) {  //区间查询
            cin >> x >> y;
            cout << sum(y) - sum(x - 1) << "\n";
        }
    }
}

//区间修改&单点查询

const int N = 2000010;
int tree[N],a[N];
int n,m;
inline int lowbit(int x) 
{
    return x & -x;
}
void add(int index, int x) //增
{
    for(int i = index; i <= n; i += lowbit(i)){
        tree[i] += x;
    }
}
int sum(int index) //区间和
{
    int ans = 0;
    for(int i = index; i ; i -= lowbit(i)){
        ans += tree[index];
    }
    return ans;
}

void solve()
{
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> a[i];
    while(m--){
        int op,x,k,y;
        cin >> op;
        if(op == 1) {
            cin >> x >> y >> k;
            add(x , k);
            add(y + 1 , -k); //差分思想
        }
        else if(op == 2) {
            cin >> x;
            cout << sum(x) + a[x] << "\n";
        }
    }
}


//区间修改&区间查询(区间加区间和)

const int N = 100005;
long long d1[N],d2[N],a[N];
int n,m;
inline int lowbit(int x) 
{
    return x & -x;
}
void add(int index, int x) //维护差分树状数组
{
    for(int i = index; i <= n; i += lowbit(i)){
        d1[i] += x;
        d2[i] += (x * index);
    }
}
void range_add(int L, int R, int x) 
{
    add(L,x); //维护d[i] 差分树状数组
    add(R + 1, -x); //维护 d[i] * i 差分树状数组
}
long long query(int index) //获取[1,index]前缀和
{
    long long res = 0;
    for(int i = index; i ; i -= lowbit(i)){
        res += (index + 1) * d1[i] - d2[i];
    }
    return res;
}
long long range_query(int L, int R) //前缀和[1,R] - 前缀和[1, L - 1]
{
    return query(R) - query(L - 1);
}                  

void solve()
{
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        add(i,a[i] - a[i-1]);
    }
    while(m--){
        int op,x,y,k;
        cin >> op;
        if(op == 1) {
            cin >> x >> y >> k;
            range_add(x,y,k);
        }
        else if(op == 2) {
            cin >> x >> y;
            cout << range_query(x,y) << "\n";
        }
    }
}


template<typename T>
struct Fenwick
{
    int n;
    vector<T> a;

    Fenwick(int n_ = 0)
    {
        init(n_ + 3);
    }

    void init(int n_)
    {
        n = n_;
        a.assign(n, T{});
    }

    void add(int pos, const T& val)
    {
        for(int i = pos + 1; i < n; i += i & -i)
        {
            a[i] = a[i] + val;
        }
    }

    T internalQuery(int pos)
    {
        T res{};
        for(int i = pos + 1; i > 0; i -= i & -i)
        {
            res = res + a[i];
        }
        return res;
    }

    T get(int l, int r)
    {
        return internalQuery(r) - internalQuery(l - 1);
    }

    int select(const T& k) 
    {
        int pos = 0;
        T cur{};
        for(int i = bit_ceil(unsigned(n)); i; i /= 2)
        {
            if(pos + i < n && cur + a[pos + i] <= k)
            {
                pos += i;
                cur = cur + a[pos];
            }
        }
        return pos;
    }
};