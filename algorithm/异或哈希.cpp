作用: 异或哈希是个很神奇的算法, 利用了异或操作的特殊性和哈希降低冲突的原理, 可以用于快速找到一个组合是否出现和序列中的数是否出现了k次


const int N = 2e5 + 10;
const int M = 1e6 + 10;
mt19937_64 rnd(time(0));
using u64 = unsigned long long;

int a[N];
u64 pre[N], hash[M]; //pre[i] 存前缀异或和, hash[i] 存哈希过后的值

for(int i = 1; i <= 1e6; i++) hash[i] = rnd(); //先哈希

for(int i = 1; i <= n; i++)
{
    cin >> a[i];
    pre[i] = pre[i - 1] ^ hash[a[i]];
}