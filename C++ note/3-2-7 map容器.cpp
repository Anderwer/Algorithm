一.map容器
1.map/multimap 也是关联式容器,容器自身有规则,通过键值排序, map 容器中的元素是对组,对组的第一个元素是键值,不能改变,第二个元素是实值,可以改变

2.map 容器和 multimap 容器的区别是 multimap 允许有相同的元素

3.数据结构:平衡二叉树

4.迭代器:双向迭代器

5.常用api:
    1.构造函数:
        map<T> mp;//map默认构造函数
        mulitmap<T> mmp;//multimap默认构造函数
        map(const set& mp); //拷贝构造函数

    2.赋值操作:
        map& operator=(const map &mp);//重载等号操作符
        swap(mp);//交换两个集合容器

    3.大小操作:
        size();//返回容器中元素的数目
        empty();//判断容器是否为空

    4.插入数据操作:
        map.insert(...);//往容器插入元素，返回pair<iterator,bool)
        map<int, string> mapStu;
        //第一种 通过pair的方式插入对象
        mapStu.insert(pair<int, string>(3,“小张”));
        // 第二种 通过pair的方式插入对象
        mapStu.inset(make_pair(-l,"校长"));
        //第三种 通过value_type的方式插入对象
        mapStu.insert(map<int, string〉::value_type(1,"小李"));
        //第四种 通过数组的方式插入值
        mapStu[3]="小刘";

    5.删除操作:
        clear();//清除所有对组
        erase(pos)://删除 pos迭代器所指的对组，返回下一个对组的迭代器pair。
        erase(beg, end);//删除区间[beg,end)的所有对组 ，返回下一个对组的迭代器pair。
        erase(elem);//删除容器中 key 为 elem的对组

    6.改变map排序规则,变为降序(从大到小)
        struct func
        {
         bool operator()(int key1, int key2)
            {
                return key1 > key2;
            }
        }
        map<int,string,func> mp//template < Key, Value, func > mp
    
    7.查询操作:
        find(key);//查找键key是否存在,若存在，返回该键的元素的迭代器;若不存在，返回map.end();
        count(keyElem);//返回容器中key为keyElem的对组个数。对map来说，要么是0，要么是1;对multimap来说可能大于1
        lower_bound(keyElem);//返回第一个key>=keyElem元素的迭代器。
        upper_boumd(kevElem);//返回第一个key>keyElem元素的迭代器。
        equal_range(keyElem)://返回容器中key与keyElem相等的上下限的两个选代器
        