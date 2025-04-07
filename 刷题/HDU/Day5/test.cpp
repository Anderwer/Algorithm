#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
const int MOD = 998244353;
 
// 这里 m 指环中模 (x^m - 1) 的 m
int global_m;
 
// 多项式用一个长度为 global_m 的vector<int>表示，
// 下标 i 表示 x^i 项的系数（所有运算均 mod MOD）。
// 我们定义： (A * B) 中，指数按照 (i+j) mod global_m 累加。
// 复杂度 O(m^2)
vector<int> polyMul(const vector<int>& A, const vector<int>& B) {
    vector<int> C(global_m, 0);
    for (int i = 0; i < global_m; i++) {
        // 为减少取模次数可提前保存 A[i]
        int Ai = A[i];
        if(Ai == 0) continue;
        for (int j = 0; j < global_m; j++) {
            C[(i+j) % global_m] = ( (ll) C[(i+j) % global_m] + (ll) Ai * B[j] ) % MOD;
        }
    }
    return C;
}
 
// 快速幂（多项式版）：计算 poly^exp (在环 Z_MOD[x] mod (x^m-1) 中)
vector<int> polyPow(vector<int> base, ll exp) {
    vector<int> res(global_m, 0);
    res[0] = 1; // 多项式1
    while(exp > 0) {
        if(exp & 1)
            res = polyMul(res, base);
        base = polyMul(base, base);
        exp >>= 1;
    }
    return res;
}
 
// 快速整数模幂
ll modExp(ll base, ll exp) {
    ll res = 1 % MOD;
    base %= MOD;
    while(exp) {
        if(exp & 1)
            res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return res;
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    ll n;
    int m;
    cin >> n >> m;
    global_m = m; // 设置全局变量
    // 将 n 写成 n = q * m + rem, 其中 rem < m 
    ll q = n / m;
    int rem = (int)(n % m);
    
    // 计算每个余数出现的次数（注意序列 [1, n]）
    // 对于余数 0：数值为 m,2m,3m,... 所以 cnt[0] = q
    // 对于 1<= r <= m-1： cnt[r] = q + (r <= rem ? 1 : 0)
    vector<ll> cnt(m, 0);
    cnt[0] = q;
    for (int r = 1; r < m; r++){
        cnt[r] = q + (r <= rem ? 1LL : 0LL);
    }
    
    // 接下来构造 m 个因子：
    // 对于余数 r，对应多项式应为 (1+x^r)^(cnt[r]) (模 x^m - 1)
    // 注意：当 r == 0 时，(1+x^0) = 1+1 = 2，所以结果即为常数 2^(cnt[0]).
    vector< vector<int> > polyFactors(m, vector<int>(m, 0));
    
    // 余数 0
    {
        // (1+x^0)^(cnt[0]) = (2)^(cnt[0]).
        ll val = modExp(2, cnt[0]);
        polyFactors[0][0] = (int) val;  // 其他指数都为0
    }
    
    // 对于余数 r (1 <= r < m)
    for (int r = 1; r < m; r++){
        // 基本多项式为 1 + x^r （注意 x^(r mod m)）
        vector<int> base(global_m, 0);
        base[0] = 1;
        base[r % m] = (base[r % m] + 1) % MOD;
        // 计算 (1+x^r)^(cnt[r]) 快速幂，
        // 由于 cnt[r] 可能非常大，所以使用二分幂
        polyFactors[r] = polyPow(base, cnt[r]);
    }
    
    // 将各个因子连乘：
    // total(x) = ∏_{r=0}^{m-1} (1+x^r)^(cnt[r]) mod (x^m-1)
    vector<int> total(global_m, 0);
    total[0] = 1;
    for (int r = 0; r < m; r++){
        total = polyMul(total, polyFactors[r]);
    }
 
    // 此时 total[0] 是包含空集的方案数，
    // 答案要求非空，所以减去空集（即1），取模 MOD
    int ans = total[0] - 1;
    if(ans < 0) ans += MOD;
    cout << ans << "\n";
 
    return 0;
}
