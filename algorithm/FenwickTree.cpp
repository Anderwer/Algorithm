template<typename T>
struct Fenwick
{
    int n;
    vector<T> a;

    Fenwick(int n_ = 0)
    {
        init(n_ + 1);
    }

    void init(int n_)
    {
        n = n_;
        a.assign(n, T{});
    }

    int lowbit(int x)
    {
        return x & -x;
    }

    void add(int pos, const T& val)
    {
        for(int i = pos; i < n; i += lowbit(i))
            a[i] = a[i] + val;
    }

    T internalQuery(int pos)
    {
        T res{};
        for(int i = pos; i; i -= lowbit(i))
            res = res + a[i];
        return res;  
    }

    T get(int l, int r)
    {
        return internalQuery(r) - internalQuery(l - 1);
    }
    
    int select(const T& k) 
    {
        int pos = 0;
        T cur{};
        for(int i = bit_ceil(unsigned(n)); i; i /= 2)
        {
            if(pos + i < n && cur + a[pos + i] <= k)
            {
                pos += i;
                cur = cur + a[pos];
            }
        }
        return pos;
    }
};