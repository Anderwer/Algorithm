一.deque容器

1.数据结构:逻辑上是连续的存储空间，实际上的由很多块定量的块空间，通过中控制连接起来

2.迭代器:随机迭代器

3.常用api:
    1.构造函数:
        deque<T> deqT;//默认构造形式
        deque(beg, end);//构造函数将[beg，end)区间中的元素拷贝给本身。
        deque(n, elem);//构造函数将n个elem拷贝给本身。
        deque(const deque& deq),//拷贝构造函数。

    2.赋值操作:
        assign(beg, end);//将[beg，end)区间中的数据拷贝赋值给本身。
        assign(n, elem);//将n个elem拷贝赋值给本身。
        deque& operator=(const deque &deq);//重载等号操作符
        swap(deq);//将 deq与本身的元素互换。

    3.大小操作:
        deque.size();//返回容器中元素的个数。
        deque.empty();//判断容器是否为空。
        deque.resize(num);//重新指定容器的长度为 num,若容器变长，则以默认值填充新位置。如果容器变短，则末尾超出容器长度的元素被删除。
        degue.resize(num, elem);//重新指定容器的长度为 num,若容器变长，则以 elem值填充新位置,如果容器变短，则末尾超出容器长度的元素被删除。

    4.双端插入和删除操作:
        push_back(elem);//在容器尾部添加一个数据
        push_front(elem);//在容器头部插入一个数据
        pop_back();//删除容器最后一个数据
        pop_front();//删除容器第一个数据

    5.存取数据操作:
        at(int idx);//返回索引 idx 所指的数据，如果idx 越界，抛出 out_of_range异常
        deque& operator[](int idx);//返回索引 idx 所指的数据，越界时，运行直接报错
        front();//返回容器中第一个数据元素
        back();//返回容器中最后一个数据元素。

    6.插入操作:
        insert(pos, elem);//在 pos 位置插入一个 elem元素的拷贝，返回新数据的位置。
        insert(pos, n, elem);//在pos 位置插入n个elem数据，无返回值。
        insert(pos, beg, end);//在pos位置插入[beg,end)区间的数据，无返回值。

    7.删除操作:
        c1ear();//移除容器的所有数据
        erase(beg, end)://删除[beg,end)区间的数据，返回下一个数据的位置。
        erase(pos)://删除 pos 位置的数据，返回下一个数据的位置。

    
