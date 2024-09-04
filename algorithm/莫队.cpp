普通莫队算法:
    如果从[L,R]的答案能在O(1)扩展到[L-1,R],[L+1,R],[L,R+1],[L,R-1]的答案,则可以在O(n√n)复杂度求出所有询问

    步骤: 先对于区间[L,R]以L为第一关键字,R为第二关键字从小到大排序,然后一步一步转移到下一个区间

    实现:
    void move(int pos, int sign)
    {
        //update nowAns
    }
    void solve()
    {
        BLOCK_SIZE = int(ceil(pow(n,0.5)));
        sort(querys + 1,querys + 1 + m);
        for(int i = 1; i <= m; i++){
            const query& q = querys[i];
            while(l > q.l) move(--l,1);
            while(r < q.r) move(++r,1);
            while(l < q.l) move(l++,-1);
            while(r > q.r) move(r--,-1);
            ans[q.id] = nowAns;
        }
    }

    模板题: P2709
    const int N = 5e4 + 10;
    int maxn;
    int a[N],b[N];
    struct node{
	    int l,r,id;
	    bool operator<(const node& t)const{
	    	if(l / maxn != t.l / maxn) return l < t.l;
	    	return (l / maxn) & 1 ? r < t.r : r > t.r;
	    }
    }query[N];
        i64 ans[N],cnt;
    void move(int pos, int sign)
    {
	    if(sign == 1){
	    	cnt += b[a[pos]] * 2 + 1;
	    	b[a[pos]]++;
	    }
	    else{
	    	b[a[pos]]--;
		    cnt -= (b[a[pos]] * 2 + 1);
	    }
    }
    void solve()
    {
	    int n,m,k;
	    cin >> n >> m >> k;
	    for(int i = 1; i <= n; i++) cin >> a[i];
	    for(int i = 1; i <= m; i++) cin >> query[i].l >> query[i].r, query[i].id = i;
	    maxn = sqrt(n);
	    sort(query + 1, query + 1 + m);
	    for(int i = 1, l = 1, r = 0; i <= m; i++){
	    	const node& q = query[i];
	    	while(l > q.l) move(--l,1);
	    	while(r < q.r) move(++r,1);
	    	while(l < q.l) move(l++,-1);
	    	while(r > q.r) move(r--,-1);
	    	ans[q.id] = cnt;
	    }
	    for(int i = 1; i <= m; i++) cout << ans[i] << "\n";
    }

    