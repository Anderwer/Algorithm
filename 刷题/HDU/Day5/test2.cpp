#include <iostream>
using namespace std;
 
typedef long long ll;
const ll MOD = 998244353;
 
// 快速幂，计算 base^exp mod mod
ll modExp(ll base, ll exp, ll mod) {
    ll res = 1 % mod;
    base %= mod;
    while(exp) {
        if(exp & 1)
            res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}
 
void solve(){
    ll n;
    cin >> n;
    
    ll r = n % 5;
    ll ans = 0;
    if(r == 0 || r == 2){
        // 情况一：n ≡ 0 或 2 (mod 5)，小凯必胜，概率为 1。
        ans = 1;
    }
    else if(r == 1){
        // 当 n = 5*k + 1
        ll k = (n - 1) / 5;
        if(k == 0){
            // n = 1，此时 G(1) = 1/2
            ans = modExp(2, MOD - 2, MOD); // 2^{-1} mod MOD
        }
        else{
            // 对于 k ≥ 1，有 G(5*k+1) = 1 - 2^{-k}
            // 根据费马小定理：2^{-k} = 2^(MOD-1-k) mod MOD
            ll inv2k = modExp(2, MOD - 1 - k, MOD);
            ans = (1 - inv2k) % MOD;
            if(ans < 0) ans += MOD;
        }
    }
    else if(r == 3){
        // n = 5*k + 3, k = (n - 3)/5, G(n)= 1 - 2^{-(k+2)}
        ll k = (n - 3) / 5;
        ll inv2 = modExp(2, MOD - 1 - (k + 2), MOD);
        ans = (1 - inv2) % MOD;
        if(ans < 0) ans += MOD;
    }
    else if(r == 4){
        // n = 5*k + 4, k = (n - 4)/5, G(n)= 1 - 2^{-(k+1)}
        ll k = (n - 4) / 5;
        ll inv2 = modExp(2, MOD - 1 - (k + 1), MOD);
        ans = (1 - inv2) % MOD;
        if(ans < 0) ans += MOD;
    }
    
    cout << ans % MOD << "\n";
}

int main()
{
    int t;
    cin >> t;
    while(t--) solve();
}