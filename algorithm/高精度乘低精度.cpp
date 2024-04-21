#include<array>
const int maxn = 1000000;//可改
typedef array<int,maxn> Arraymaxn;
Arraymaxn ans;
int t = 1;//初始化位数
Arraymaxn mult(Arraymaxn& res,int b)
{
	for(int i = 0; i < t; i++) res[i] *= b;
	//处理进位
    for(int i = 0; i < t; i++){
		if(res[i] >= 10){
        	res[i+1] += res[i] / 10;
        	res[i] %= 10;
			t = max(t,i+1);//判断是否需要更新答案位数
		}
    }
    return res;
}
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	ans[1] = 1;
	for(int i = 2; i <= 10; i++) ans = mult(ans,i);
	while(ans[t] == 0) t--;//去除前导0
	for(int i = t; i >= 1; i--) cout<<ans[i];
	return 0;
}