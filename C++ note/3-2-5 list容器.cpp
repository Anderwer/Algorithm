一.list容器

1.数据结构:双向循环链表

2.迭代器:双向迭代器

3.常用api:
    1.构造函数:
        list<T> lstT;//list采用采用模板类实现,对象的默认构造形式:
        list(beg, end);//构造函数将[beg，end)区间中的元素拷贝给本身
        list(n, elem);//构造函数将n个elem 拷贝给本身
        list(const list &lst)//拷贝构造函数。

    2.插入和删除操作:
        push_back(elem);//在容器尾部加入一个元素
        pop_back();//删除容器中最后一个元素
        push_front(elem);//在容器开头插入一个元素
        pop_front();//从容器开头移除第一个元素
        insert(pos, elem);//在pos位置插elem元素的拷贝，返回新数据的位置
        insert(pos, n, elem);//在pos位置插入n个elem数据，无返回值。
        insert(pos, beg, end);//在pos位置插入[beg,end)区间的数据，无返回值
        clear();//移除容器的所有数据
        erase(beg, end);//删除[beg,end)区间的数据，返回下一个数据的位置
        erase(pos);//删除pos位置的数据，返回下一个数据的位置。
        remove(elem);//删除容器中所有与elem值匹配的元素。
        remove_if(func()); //删除符合条件的元素,条件func自定

    3.大小操作:
        size();//返回容器中元素的个数
        empty();//判断容器是否为空
        resize(num);//重新指定容器的长度为num,若容器变长，则以默认值填充新位置。如果容器变短，则末尾超出容器长度的元素被删除
        resize(num, elem);//重新指定容器的长度为num，若容器变长，则以elem值填充新位置。如果容器变短，则末尾超出容器长度的元素被删除

    4.赋值和存取操作:
        assign(beg, end);//将[beg,end)区间中的数据拷贝赋值给本身。
        assign(n, elem);//将n个elem拷贝赋值给本身。
        list& operator=(const list &lst);//重载等号操作符
        swap(lst);//将lst与本身的元素互换。
        front();//返回第一个元素
        back();//返回最后一个元素

    5.反转和排序操作:
        reverse();//反转链表，比如lst包含1,3,5元素，运行此方法后，lst就包含5,3,1元素。
        sort(func);//list 根据 func 排序
        注意:list容器不能使用algorithm库中的sort排序,只能使用其成员函数sort(func) ,其中func 自定

    