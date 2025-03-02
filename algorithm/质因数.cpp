
struct Prime
{
    const static int N = 1E6 + 10;
	bitset<N> vis;
	vector<int> P;

	void Erat_Prime() //埃氏筛 O(nloglogn), bitset优化后小于 O(n)
    {
        vis.set();
        vis[0] = vis[1] = 0;
        for(int i = 2; i * i < N; i++) if(vis[i]) for(int j = i << 1; j < N; j += i) vis[j] = 0;
        for(int i = 2; i < N; i++) if(vis[i]) P.push_back(i);
    }

    void Euler_Prime() //欧拉筛 O(n)
    {
        vis.set();
        vis[0] = vis[1] = 0;
        int cnt = 0;
        for(int i = 2; i < N; i++)
        {
            if(vis[i]) P.push_back(i), cnt++;
            for(int j = 0; j < cnt && i * P[j] < N; j++)
            {
                vis[i * P[j]] = 0;
                if(i % P[j] == 0) break;
            }
        }
    }

    vector<int> Erat_gcd(int x) //配合埃氏筛获取质因数 O(√(n / lnn))
    {
        vector<int> res;
        if(x == 2 || x == 3)
        {
            res.push_back(x);
            return res;
        }
        for(auto v : P)
        {
            if(v * v > x) break;
            if(x % v == 0)
            {
                res.push_back(v);
                while(x % v == 0) x /= v;
            }
        }
        if(x != 1) res.push_back(x);
        return res;
    }

    vector<int> gcdcnt(int x) //朴素获取质因数 O(√n)
    {
        vector<int> res;
        for(int i = 2; i * i <= x; i++)
        {
            if(x % i == 0)
            {
                while(x % i == 0) x /= i;
                res.push_back(i);
            }
        }
        if(x != 1) res.push_back(x);
        return res;
    }
	
};
