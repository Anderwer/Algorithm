#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

const int N = 2e5 + 10;
const int M = 1e6 + 10;
int a[N], cnt[M], ans[N];
int block_size;
int res;

struct node
{
    int l, r, id;
    bool operator <(const node& t) const
    {
        if(l / block_size != t.l / block_size) return l < t.l;
        return (l / block_size) & 1 ? r < t.r : r > t.r;
    }
}query[N];

void move(int pos, int flag)
{
    if(flag == 1) //添加
    {
        cnt[a[pos]]++;
        if(cnt[a[pos]] & 1) res++;
        else res--;
    }
    else
    {
        cnt[a[pos]]--;
        if(cnt[a[pos]] & 1) res++;
        else res--;
    }
}

void solve()
{
    int n, q;
    cin >> n >> q;
    for(int i = 1; i <= q; i++) ans[i] = 0;
    
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i];
        cnt[a[i]] = 0;
    }
    for(int i = 1; i <= q; i++) cin >> query[i].l >> query[i].r, query[i].id = i;
    block_size = sqrt(n);
    sort(query + 1, query + 1 + q);

    int L = 1;
    int R = 0;
    res = 0;
    for(int i = 1; i <= q; i++)
    {
        auto now = query[i];
        while(L > now.l) move(--L, 1); //扩大区间, 添加
        while(R < now.r) move(++R, 1);
        while(L < now.l) move(L++, -1); //缩小区间，删除
        while(R > now.r) move(R--, -1);
        ans[now.id] = res;
    }
    for(int i = 1; i <= q; i++)
    {
        if(ans[i] != 0) cout << "NO\n";
        else cout << "YES\n";
    }
}
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}

/*
如果只有2个不同的数 : 警长必输
如果只有2个相同的数 : 平局
三个数 a, b, c: 则警长必输

区间长度为奇数则必输
区间长度为偶数且区间内所有不同的数都有偶数个则才能平局


[2, 2, 2, 3, 3]
*/
