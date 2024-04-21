一.stack容器

1.数据结构:连续的存储空间,只有一个出口,先进后出特性

2.迭代器:没有迭代器

3.常用api:
    1.构造函数:
        stack<T> stkT;//stack采用模板类实现, stack 对象的默认构造形式:
        stack(const stack &stk);//拷贝构造函数

    2.赋值操作:
        stack& operator=(const stack &stk);//重载等号操作符

    3.数据存取操作:
        push(elem)//问栈顶添加元素
        pop();//从栈顶移除第一个元素。
        top();//返回找顶元素。

    4.大小操作:
        empty();//判断堆栈是否为空
        size();//返回堆栈大小

二.queue容器

1.数据结构:连续的存储空间,有两个口,一个是进入数据,一个是出数据,有先进先出特性

2.迭代器:没有迭代器

3.常用api:
    1.构造函数:
        queue<T> queT;//queue 采用模板类实现, queue 对象的默认构造形式:
        queue(const queue &que);//拷贝构造函数

    2.赋值操作:
        queue& operator=(const queue &que);//重载等号操作符

    3.数据存取操作:
        push(elem)//问队尾添加元素
        pop();//从队头移除第一个元素。
        back();//返回最后一个元素
        front();//返回第一个元素

    4.大小操作:
        empty();//判断队列是否为空
        size();//返回队列大小

        