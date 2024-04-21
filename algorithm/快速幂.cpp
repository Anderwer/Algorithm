int qpow(int a, long long b, int p)
{
	int res = 1;
	for(; b; b!=2, a = 1LL * a * a % p) if(b % 2) res = 1LL * res * a % p;
	return res;
}

auto quick_pow = [&](auto&& self,ll a,ll b,ll p)->ll{ // 求a^b,且取模
    	if(b == 0) return 1;
    	ll res = self(self,a, b >> 1,p);
    	res = 1LL * res * res % p;
    	if(b % 2 == 1) res = 1LL * res * a % p;
    	return res;
	};

快速乘

auto mul = [&](ll a,ll b,ll p)->ll{
		ll res=0;
		while(b){
			if(b & 1) res = (res + a) % p;
			a = (a + a) % p;
			b >>= 1;
		}
		return res;
	};


快速乘快速幂

auto mul = [&](ll a,ll b,ll p)->ll{ //快速乘
		ll res=0;
		while(b){
			if(b & 1) res = (res + a) % p;
			a = (a + a) % p;
			b >>= 1;
		}
		return res;
	};
	
	auto quick_pow = [&](ll a,ll b,ll p)->ll{ // 快速乘快速幂
    	ll res = 1;
    	while(b){
    		if(b & 1) res = mul(res, a, p);
    		a = mul(a, a, p);
    		b >>= 1;
    	}
    	return res;
	};
-------------------------------------------------
                  //高精度下的快速幂
#include<array>
#include<iostream>
using namespace std;
typedef array<int, 1000> Arraymaxn;
Arraymaxn a, b, ans;
int t = 500;
Arraymaxn mult1(Arraymaxn& a, Arraymaxn& b)
{
    Arraymaxn res{ 0 };
    for (int i = 0; i < t; i++) {
        for (int j = 0; j < t; j++) {//此题控制位数为500,则for循环500终止
            if (i + j >= t) continue;//如果结果需要500位,可以剪枝
            res[i + j] += a[i] * b[j];
        }
    }
    //处理进位
    for (int i = 0; i < t; i++) {
        if (res[i] >= 10) {
            res[i + 1] += res[i] / 10;
            res[i] %= 10;
            t = max(t, i + 1);
        }
    }
    return res;
}

Arraymaxn mult2(Arraymaxn& res, int b)
{
    for (int i = 0; i < t; i++) res[i] *= b;
    //处理进位
    for (int i = 0; i < t; i++) {
        if (res[i] >= 10) {
            res[i + 1] += res[i] / 10;
            res[i] %= 10;
            t = max(t, i + 1);//判断是否需要更新答案位数
        }
    }
    return res;
}
Arraymaxn quick_pow(int a, int b, Arraymaxn& res) // 求a^b
{
    if (b == 0) return res;
    res = quick_pow(a, b >> 1, res);
    res = mult1(res, res);
    if (b % 2 == 1) res = mult2(res, a);
    return res;
}
int main()//不足500位高位补0
{
    int p,a = 2;
    cin >> p;
    int cnt = (int)(p * log10(2)) + 1;
    cout<< cnt <<"\n";
    ans[0] = 1;//初始化
    quick_pow(a, p, ans);
    ans[0] -= 1;
    if(cnt >= 500){
    	for(int i = 499;i >= 0; i--){
    		cout<<ans[i];
    		if(i % 50 == 0) cout<<"\n";
    	}
    }
    else{
    	int num = 500 - cnt;
    	for(int i = 1; i < num; i++){
    		cout<<0;
    		if(i % 50 == 0) cout<<"\n";
    	}
    	for(int i = cnt; i >= 0; i--){
    		cout<<ans[i];
    		if(num % 50 == 0) cout<<"\n";
    		num++;
    	}
    }
    return 0;
}