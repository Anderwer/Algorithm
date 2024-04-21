一.vector容器

1.数据结构:连续存储空间

2.迭代器:随机迭代器

3.vector容器动态增长原理:
    1.当存储空间不够时,会开辟另一块更大的空间,然后把数据拷贝过去,最后再销毁原来的空间
    2.申请的空间会比用户需求的更大一些
    3.重新分配空间,那么原来的迭代器就会失效

4.vector常用api:
    1.构造函数:
        vector<T> v ;//采用模板实现类实现，默认构造函数
        vector(v.begin(), v.end());//将v[begin()，end())区间中的元素拷贝给本身。
        vector(n, elem);//构造函数将n个elem拷贝给本身。
        vector(const vector &vec);//拷贝构造函数。

    2.常用的赋值操作:
        assign(beg, end);//将[beg，end)区间中的数据拷贝赋值给本身。
        assign(n, elem);//将n个elem拷贝赋值给本身。
        vector& operator=(const vector &vec)://重载等号操作符
        swap(vec);//将vec与本身的元素互换。

    3.vector大小操作:
        size();//返回容器中元素的个数。
        empty();//判断容器是否为空.
        resize(int num);//重新指定容器的长度为 num，若容器变长，则以默认值填充新位置。如果容器变短，则末尾超出容器长度的元素被删除。
        resize(int num, elem);//重新指定容器的长度为num，若容器变长，则以elem值填充新位置。如果容器变短，则末尾超出容器长度的元素被删除。
        capacity();//容器的容量
        reserve(int len);//容器预留len个元素长度，预留位需不初始化，元素不可访问。

    4.vector数据存取操作:
        at(int idx);//返回索引 idx 所指的数据，如果idx 越界，抛出 out_of_range异常
        vector& operator[](int idx);//返回索引 idx 所指的数据，越界时，运行直接报错
        front();//返回容器中第一个数据元素
        back();//返回容器中最后一个数据元素。

    5.vector插入和删除操作:
        insert(const_iterator pos, int count, ele);//选代器指向位置 pos 插入 count 个元素 ele
        push_back(ele);//尾部插入元素 elev
        pop_back();//删除最后一个元素
        erase(const_iterator start, const_iterator end);//删除选代器从 start到 end之间的元素
        erase(const_iterator pos);//删除选代器指向的元素
        clear()://删除容器中所有元素。

    