//Sparse Table       O(nlogn)的预处理，O(1)的查询
//对大量区间问题询问的解法
//采用动态规划思想

dp[i][j] //表示从i开始，长度为2^j(2的j次方)的区间,也就是[i,i+2^j-1]区间的max最大值
         //具体原理:任意区间的长度都可以转化为二进制 

对于某次询问区间[L,R]
区间长度len= R - L + 1
j = log2(len);
ans = max(dp[L][j], dp[R-(2^j)+1][j]) 其中第二个区间的左端点可以类比上面求区间长度,只是len变为了2^j

预处理：
   1. dp[i][0] = arr[i];
   2. dp[i][j] = max(dp[i][j-1] , dp[i+2^(j-1)][j-1])//以i为起点,在长度为2^j的区间中,区间对半分成[i,i+2^(j-1)-1]和[i+2^(j-1),i+2^j-1]

ST表可以用来求形如f(a,a) = a的函数性质,如max , min , gcd(最大公约数) , lcm(最小公倍数)

ST表为静态表,只能处理离线问题

代码实现:
int query(int L,int R)
{
    int j = (int) log2(R - L + 1);
    return max(dp[L][j], dp[R - (1 << j) + 1][j]);
}
int main()
{
    int arr = {...};
    int dp[n][(int) log2(n) + 5];//创建长度为n的数据的dp
    for(int i = 0; i < n; i++) dp[i][0] = arr[i];
    for(int j = 1; j <= log2(n); j++){//先枚举区间长度
        for(int i = 0; i + (1 << j) - 1 < n; i++){//再枚举区间左端点,边界条件为右端点到底,即i + (1 << j) - 1 < n, (1 << j)表示 2^j
            dp[i][j] = max(dp[i][j-1], dp[i + (1 << (j - 1))][j-1]);
        }
    }
    int l,r;
    while(cin>>l>>r){
        cout<<query(l,r)<<"\n";
    }
}

const int N = 500005;
int st[N][31];
int a[N];
int n;
void init()
{
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) st[i][0] = a[i];
    for(int j = 1; j <= __lg(n); j++){
        for(int i = 1; i + (1 << j) - 1 <= n; i++){
            st[i][j] = max(st[i][j-1],st[i + (1 << (j - 1))][j - 1]);
        }
    }
}
int query(int l, int r)
{
    int k = __lg(r - l + 1);
    return max(st[l][k],st[r - (1 << k) + 1][k]);
}

int main()
{
    int m;
    cin >> n >> m;
    init();
    while(m--){
        int l,r;
        cin >> l >> r;
        cout << query(l,r) << "\n";
    }
    return 0;
}