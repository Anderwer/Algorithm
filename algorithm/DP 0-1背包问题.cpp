//利用动态规划求出装背包后价值最大值
#include<iostream>
#include<algorithm>
using namespace std;
int f[5][9];//4种物品，背包容量为8，数组均都多1是因为要给0行和0列空位置
int w[5] = {0,2,3,4,5};//4种物品各自的重量, 物品从下标为1开始
int v[5] = {0,3,4,5,8};//4种物品各自的价值, 物品从下标为1开始
int main()
{
    int i,j;
    memset(f,0,sizeof(f));//初始化
    for(int i = 1; i < 5; i++){//循环遍历4种物品
        for(int j = 1; j < 9; j++){//循环遍历背包容量
            if(w[i] > j) f[i][j] = f[i-1][j];//如果物品重量大于背包容量，则不装物品，价值继承选上一个物品时的状态
            else f[i][j] = max(f[i-1][j] , f[i-1][j-w[i]] + v[i]);
                 // 当前可选择装或不装，并在两者中选择最优
        }        //在装的情况下,f[i-1][j-w[i]] + v[i]则是指装完当前物品后，获取上一个物品时背包容量在j-w[i]情况下的最优解 + 当前物品价值 
    }
    return 0;
}

0-1背包问题        状态方程 f(j) = max( f(j) , f(j - w[i]) + v[i] )   倒序循环
for (int i = 1; i <= n; i++)
  for (int l = W; l >= w[i]; l--) f[l] = max(f[l], f[l - w[i]] + v[i]);


分组背包
for (int k = 1; k <= ts; k++)          // 循环每一组
  for (int i = m; i >= 0; i--)         // 循环背包容量
    for (int j = 1; j <= cnt[k]; j++)  // 循环该组的每一个物品
      if (i >= w[t[k][j]])             // 背包容量充足
        dp[i] = max(dp[i],
                    dp[i - w[t[k][j]]] + c[t[k][j]]);  // 像0-1背包一样状态转移


完全背包    状态方程 f(i,j) = max( f(i,j) , f(i,j-w[i]) + v[i] ) 因此要正序循环
for(int i = 2; i <= n; i++){ //完全背包
	for(int j = w[i]; j <= 总容量; j++){
		dp[j] = max(dp[j],dp[j-w[i]] + v[i]);
	}
}

