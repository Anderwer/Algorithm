拓扑排序要解决的问题是给一个有向无环图的所有节点排序。
可用于判断图中是否存在环或者获取拓扑序列

Kahn(卡恩)算法:
e[N] 存点x的邻点 , tp 存拓扑序列, din[N] 存 所有点的入度
算法核心思想:利用队列来维护一个入度为0的点的集合

vector<int> e[N];
vector<int> tp;
int din[N];
int n,m;

bool topsort()
{
    queue<int> q;
    for(int i = 1; i <= n; i++){
        if(din[i] == 0) q.push(i); //1. 初始化,将所有入度0的点压入队列中
    }
    while(!q.empty())
    {
        int x = q.front;
        q.pop();
        tp.push_back(x); //2. 每次从队列中取出一个x,并放到tp序列中
        for(auto &y : e[x]) if(--din[y] == 0) q.push(y); //3. 将x的所有出边删除,并判断x所连接的点是否入度为0,如果为0就压入队列中
    }
    return tp.size() == n; //判断tp中元素个数是否为n, 如果不为n则图中存在环
}

int main()
{
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        cin >> a >> b;
        e[a].push_back(b);
        din[b]++;
    }
    if(!toopsort()) cout  << "有环";
    else for(auto &e : tp) cout << e << " ";
    return 0;
}

