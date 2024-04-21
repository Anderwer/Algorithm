
#include<array>
const int maxn = 10000;
typedef array<int,maxn> Arraymaxn;
Arraymaxn ans,tmp1,tmp2;
int t = 1;//存储位数
void init(int x,Arraymaxn& y)
{
    int cnt = 1;
    while(x){
        y[cnt] = x % 10;
        x /= 10;
        cnt++;
    }
    t = max(t,cnt);
}
Arraymaxn sum(Arraymaxn& a,Arraymaxn& b)
{
    for(int i = 1; i <= t; i++) a[i] += b[i];
    for(int i = 1; i <= t; i++){
        if(a[i] >= 10){
            a[i+1] += a[i] / 10;
            a[i] %= 10;
            t = max(t,i+1);
        }
    }
    return a;
}
int main()
{
    int m = 1264652065;
    int n = 848616064;
    init(m,tmp1);
    init(n,tmp2);
    ans = sum(tmp1,tmp2);
    while(ans[t] == 0) t--;
    for(int i = t; i >= 1; i--) cout<<ans[i];
    return 0;
}