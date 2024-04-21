//全排列
#include<iostream>
#include<cmath>
using namespace std;  
//n个数全排列 ：一定要知道在第几层，该数现在的状态，回溯时的状态 
int n;
int a[1000];
bool flag[1000];
void dfs(int k){
	if(k==n+1){  //递归结束条件，当到达第n+1层，代表第n层已经填完 
		//输出解
		return;
	}
	for(int i=1; i<=n; i++){  //n个数字 
		if(flag[i]==0){  //当前数字没用过才可以排列 
			a[k]=i;   //第k层（第k个位置）填数字i
			flag[i]=1;  //该数已经用过，置为1
			dfs(k+1);    //填下一层（下一个位置）
			flag[i]=0;   //递归回来的时候需要重新置为0 
		}
	}
}
int main(){
	cin>>n;
	dfs(1);  //从第一层（第一个位置）开始排列 
	return 0;
}

//n个数选m个数全排列

#include<iostream>
#include<cmath>
using namespace std;  
//n个数选m个数全排列 ：一定要知道在第几层，该数现在的状态，回溯时的状态 
int n,m;
int a[1000];
bool flag[1000];
void dfs(int k){
	if(k==m+1){  //递归结束条件，当到达第m+1层，代表第m层已经填完 
		//输出解
		return;
	}
	for(int i=1; i<=n; i++){  //n个数字 
		if(flag[i]==0){  //当前数字没用过才可以排列 
			a[k]=i;   //第k层（第k个位置）填数字i
			flag[i]=1;  //该数已经用过，置为1
			dfs(k+1);    //填下一层（下一个位置）
			flag[i]=0;   //递归回来的时候需要重新置为0 
		}
	}
}
int main(){
	cin>>n>>m;
	dfs(1);  //从第一层（第一个位置）开始排列 
	return 0;
}

//n个不同的元素，任取m个数进行组合。（组合无序）

#include<iostream>
#include<cmath>
using namespace std;  
//n个数选m个数组合 ：当前位置数值比前一个数至少大1，
//a[k]代表当前位置上的值，它的范围是[a[k-1]+1,n] 

int n,m;
int a[1000];
void dfs(int k){
	if(k==m+1){  //递归结束条件，当到达第m+1层，代表第m层已经填完 
		for(int i=1; i<=m; i++){
			cout<<a[i]<<" ";
		}cout<<endl; 
		return;
	} 
	//当前位置数值比前一个数至少大1，a[k]代表当前位置上的值，它的范围是[a[k-1]+1,n] 
	for(int i=a[k-1]+1; i<=n; i++){  
		a[k]=i;   //第k层（第k个位置）填数字i
		dfs(k+1);    //填下一层（下一个位置）
	}
}
int main(){
	cin>>n>>m;
	dfs(1);  //从第一层（第一个位置）开始排列 
	return 0;
}


//此外，还可以借助next_permutation函数进行全排列
//如果是对其中k个数进行排列或者组合时可以借助辅助序列，将其中k个数设为0，另外n-k个数设为1
//这样就可以得到有关0,1的排列组合
//下列方法是利用STL解法
#include<iostream>
#include<algorithm>
using namespace std;  

int n,m;
int pos[1000];
//n个不同的元素，任取m个数进行组合。（组合无序）
int main(){
	cin>>n>>m;
	for(int i = m + 1; i <= n; i++) pos[i] = 1;//构造位置函数，让n-m个数设为1
	do{
		for(int i = 1; i <= n; i++){
			if(pos[i] == 0) cout<< i <<" ";
		}
		cout<<endl;
	}while(next_permutation(pos+1,pos+1+n));
	return 0;
}
