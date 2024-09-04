数位DP的特点 : 求某个区间[L,R]内,满足某种性质的数的个数

数位DP的技巧1 : 类似前缀和思想,转化为[0,R] - [0,L - 1] 求解

数位DP的技巧2 : 从高位到低位填数,要 分类讨论:
    把整数R的每一位分解,存入数组a,则 R = a[n]a[n-1]a[n-2]...a[1]
    从高位到低位填数,划分两类 : 0 ~ a[i] - 1 和 a[i]
    如果第i位填 0 ~ a[i] - 1 ,则后面的每一位可以填 0~9
    如果第i位填 a[i], 则再讨论下一位,保证填的数不超过R

代码模板 :
    先对数集从低位到高位做预处理
    再对数集从高位到低位做递推

模板题 : LibreOJ - 10164 数字游戏
    指定一个整数闭区间 [a,b], 问这个区间内有多少个不降数.
    不降数例如 : 123, 226
    1 <= a,b <= 2.1e9

代码部分:
using i64 = long long;
using namespace std;
const int N = 12;
int a[N];
i64 dp[N][N]; //dp[i][j] : 一共有i位且最高位为j的不降数有多少
void init()
{
	for(int i = 0; i < 10; i++) dp[1][i] = 1;
	for(int i = 2; i < 11; i++){ //枚举位数
		for(int j = 0; j < 10; j++){ //枚举最高位
			for(int k = j; k < 10; k++){ //枚举最高位的后一位数
				dp[i][j] += dp[i - 1][k];
			}
			//printf("dp[%d][%d] = %d\n",i,j,dp[i][j]);
		}
	}
}
i64 query(int x)
{
	if(x == 0) return 1;
	i64 res = 0;
	int cnt = 0, last = 0;
	while(x) a[++cnt] = x % 10, x /= 10; //拆位
	for(int i = cnt; i > 0; i--){ //从最高位枚举
		int now = a[i];
		for(int j = last; j < now; j++){ //枚举当前位可填入数字为[last,a[i] - 1],因为要不降数则不能比前面last小
			res += dp[i][j]; //累加
		}
		if(now < last) break; //如果出现当前位比上一位小,则不符合规则且找不到别的方案,退出计数
		last = now; //更新last
		if(i == 1) res++; //如果能走到本身x,则让方案数 + 1
	}
	return res;
}
void solve()
{
	init();
	int l,r;
	while(cin >> l >> r){
		cout << query(r) - query(l - 1) << "\n";
	}
}