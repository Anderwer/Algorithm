#include <bits/stdc++.h>
#define lc k << 1
#define rc k << 1 | 1
using i64 = long long;
using namespace std;
const int N = 3e5 + 10;
int last[N], a[N];
struct node
{
    int L, R, mx, mn;
}tree[N << 2];
int n;

void build(int k, int L, int R)
{
    tree[k].L = L;
    tree[k].R = R;
    if(L == R)
    {
        tree[k].mx = a[L];
        tree[k].mn = a[L];
        return;
    }
    int mid = (L + R) / 2;
    build(lc, L, mid);
    build(rc, mid + 1, R);
    tree[k].mx = max(tree[lc].mx, tree[rc].mx);
    tree[k].mn = min(tree[lc].mn, tree[rc].mn);
}

void update(int k, int i)
{
    if(tree[k].L == tree[k].R && tree[k].L == i)
    {
        tree[k].mx = 0;
        tree[k].mn = 1e9;
        return;
    }
    int mid = (tree[k].L + tree[k].R) / 2;
    if(i <= mid) update(lc, i);
    else update(rc, i);
    tree[k].mx = max(tree[lc].mx, tree[rc].mx);
    tree[k].mn = min(tree[lc].mn, tree[rc].mn);
}

int query(int k, int L, int R, int op)
{
    if(op == 0)
    {
        if(L <= tree[k].L && R >= tree[k].R) return tree[k].mx;
        int mid = (tree[k].L + tree[k].R) / 2;
        int Max = -1e9;
        if(L <= mid) Max = max(Max, query(lc, L, R, op));
        if(R > mid) Max = max(Max, query(rc, L, R, op));
        return Max;
    }
    else
    {
        if(L <= tree[k].L && R >= tree[k].R) return tree[k].mn;
        int mid = (tree[k].L + tree[k].R) / 2;
        int Min = 1e9;
        if(L <= mid) Min = min(Min, query(lc, L, R, op));
        if(R > mid) Min = min(Min, query(rc, L, R, op));
        return Min;
    }
}

void solve()
{
    int num = 0;
    cin >> n;
    vector<int> pos[n + 1];
    for(int i = 1; i <= n; i++) last[i] = 0;
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i];
        if(last[a[i]] == 0) num++;
        last[a[i]] = i;
        pos[a[i]].push_back(i);
    }
    build(1, 1, n);

    set<int> s; //维护 r
    for(int i = 1; i <= n; i++) s.insert(last[a[i]]);

    int l = 1, r = *s.begin();
    vector<int> ans;
    for(int i = 1; i <= num; i++)
    {
        if(i & 1) //找最大
        {
            //cout << l << " " << r << "\n";
            int mx = query(1, l, r, 0);
            ans.push_back(mx);
            s.erase(last[mx]);
            for(auto v : pos[mx]) update(1, v);
            for(int j = l; j <= r; j++)
            {
                
                if(mx == a[j])
                {
                    l = j;
                    break;
                }
            }
            if(l == r || mx == a[r]) r = *s.begin();
            l++;
        }
        else //找最小
        {
            //cout << l << " " << r << "\n";
            int mn = query(1, l, r, 1);
            ans.push_back(mn);
            s.erase(last[mn]);
            for(auto v : pos[mn]) update(1, v);
            for(int j = l; j <= r; j++)
            {
                if(mn == a[j])
                {
                    l = j;
                    break;
                }
            }
            if(l == r || mn == a[r]) r = *s.begin();
            l++;
        }
    }
    cout << ans.size() << "\n";
    for(auto v : ans) cout << v << " ";
    cout << "\n";
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
