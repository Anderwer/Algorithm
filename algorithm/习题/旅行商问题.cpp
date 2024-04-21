// Problem: P1433 吃奶酪
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P1433
// Memory Limit: 128 MB
// Time Limit: 1000 ms
// Powered by CP Editor (https://cpeditor.org)
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
#include<stack>
#include<queue>
#include<sstream>
#include<string>
#include<iomanip>
using namespace std;
struct node{
	double x,y;
	int num,mark;
}arr[16];
int n;
double dp[16][66000];
double x_min = 1000;
double s(node a, node b)//计算距离
{
	return sqrt((a.x - b.x)*(a.x-b.x) + (a.y - b.y)*(a.y - b.y));
}
void dfs(int step,node last,int seq,double x)//step选了几个,last为当前选的点的状态,seq传递状压中的顺序,x表示两点距离
{
	if(step == n) {if(x_min > x) x_min = x; return;}//记录最大值的最小值
	for(int i = 0; i < n; i++){//i表示当前选点
		if(arr[i].mark == 1) continue; //剪枝1
		int seq_ = seq + (1 << i);
		int pre = last.num;//上一个选点是几
		if(dp[i][seq_] == 0 || dp[i][seq_] > dp[pre][seq] + s(arr[pre],arr[i])){//剪枝2
			dp[i][seq_] = dp[pre][seq] + s(last,arr[i]);
			arr[i].mark = 1;//更新
			dfs(step+1,arr[i],seq_,x + s(last,arr[i]));
			arr[i].mark = 0;//恢复
		}
	}
}
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i = 0; i < n; i++) {cin >> arr[i].x >> arr[i].y; arr[i].num = i;}
	node start = {0,0,0,1};
	dfs(0,start,0,0);
	cout<<fixed<<setprecision(2)<<x_min;
	return 0;
}//总思路:以不同起点为开头寻找,每次选择都不相同(dfs),记录不同开头的各种选法的最优解(DP),比较各DP结果得出全局最优解
//将数据存入结构体,并记录它是第几位
//因为N <= 15,可以利用dfs(剪枝)遍历,状压DP记录最优,O((n^2)*(2^n))),700万
//dp[i][j + 2 ^ i]表示当前选到i时,j所表示的二进制序列(逆序)排列状态下的最短距离
//如果第i个点选过，则continue(剪枝1)
//dp[pre][j]表示选i前选了pre,比较dp[pre][j] + s(pre,i) 和 dp[i][j + 2 ^ i] 的大小,选择较小为最优(剪枝2)
//j表示出15个组合，而2^0 = 1,因此j <= 32768;创建dp[16][35000] = -1;
//递归结束时,比较每种情况的路程,并更新出最小值x_min,为最终答案
