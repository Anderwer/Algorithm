一.set容器
1.set容器是关联式容器,容器自身有规则,通过键值排序, set容器中的元素是键值也是实值

2.set 容器和 multset 容器的区别是 multset 允许有相同的元素

3.数据结构:平衡二叉树

4.迭代器:双向迭代器

5.常用api:
    1.构造函数:
        set<T> st;//set默认构造函数
        mulitset<T> mst;//multiset默认构造函数
        set(const set& st); //拷贝构造函数

    2.赋值操作:
        set& operator=(const set &st);//重载等号操作符
        swap(st);//交换两个集合容器

    3.大小操作:
        size();//返回容器中元素的数目
        empty();//判断容器是否为空

    4.插入和删除操作:
        insert(elem);//在容器中插入元素,返回迭代器pair<set<>::iterator,bool>。
        clear();//清除所有元素
        erase(pos)://删除 pos迭代器所指的元素，返回下一个元素的迭代器pair。
        erase(beg, end);//删除区间[beg,end)的所有元素 ，返回下一个元素的迭代器pair。
        erase(elem);//删除容器中值为 elem的元素

    5.改变set排序规则,变为降序(从大到小)
        struct func
        {
         bool operator()(int v1, int v2)
            {
                return v1 > v2;
            }
        }
        set<int, func> st; //template < 类型, 默认排序 > st

    6.查询操作:
        find(key);//查找键key是否存在,若存在，返回该键的元素的迭代器;若不存在，返回set.end();
        count(key);//查找键key的元素个数
        lower_bound(keyElem);//返回第一个key>=keyElem元素的迭代器
        upper_bound(keyElem);//返回第一个key>keyElem元素的迭代器。
        egual_range(keyElem);//返回容器中key与keyElem相等的上下限的两个迭代器
