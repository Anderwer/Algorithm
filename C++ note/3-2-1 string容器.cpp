一.string容器

1.数据结构:连续的储存空间,用一个char* 指向这片空间

2.迭代器:随机访问迭代器

3.常用api:
    1.构造函数:
        string();//创建一个空的字符串
        string(const string& str); //使用一个string对象初始化另一个string对象
        string(const char* s); //使用字符串s初始化
        string(int n, char c); //使用n个字符c初始化

    2.基本赋值操作:
        string& operator=(const char* s); //赋值给当前的字符串
        string& operator=(const string& s); //赋值给当前的字符串 
        string& operator=(char c);  //把字符赋值给当前字符串
        string& assign(const char* s); //把字符串s赋值给当前字符串
        string& assign(const string& s); //把字符串s赋值给当前字符串
        string& assign(const char* s, int n); //把字符串s的前n个字符赋值给当前字符串
        string& assign(int n, char c); //用n个字符c赋给当前字符串
        string& assign(const string& s, int start, int n); //将s从start开始,n个字符赋值给当前字符串

    3.存取字符操作:
        char& operator[](int n); //通过[]方式取字符
        char& at(int n); //通过at方式获取字符
        注意: [] 和 at 的区别:[] 访问元素时,越界不抛异常,直接挂;at越界会抛出异常

    4.拼接操作:
        string& operator+=(const string& str); //重载+=
        string& operator+=(const char* str); //重载+=
        string& operator+=(char c); //重载+=
        string& append(const char* str); //把字符串str连接到当前字符串结尾
        string& append(const string& str); //把字符串str连接到当前字符串结尾
        string& append(const char* str, int n); //把字符串str的前n个字符连接到当前字符串结尾
        string& append(const string& str, int pos, int n); //把字符串str从pos开始的n个字符连接到当前字符串结尾
        string& append(int n, char c); //在当前字符串结尾添加n个字符c

    5.查找和替换操作:
        int find(const string& str, int pos = 0) const; //从pos开始查找str第一次出现的位置
        int find(const char* str, int pos = 0) const; //从pos开始查找str第一次出现的位置
        int find(const char* str, int pos, int n) const; //从pos开始查找str的前n个字符第一次出现的位置
        int find(const char c, int pos = 0) const; //查找字符c第一次出现的位置
        int rfind(const char* str, int pos = npos) const; //查找str最后一次出现的位置,从pos开始找
        int rfind(const string& str, int pos = npos) const; //查找str最后一次出现的位置,从pos开始找
        int rfind(const char* str, int pos, int n) const; //从pos开始查找str的前n个字符出现的最后一次位置
        int rfind(const char c,int pos = 0) const; //查找字符c出现的最后一次位置
        string& replace(int pos, int n, const string& str); //替换从pos开始的n个字符为str
        string& replace(int pos, int n, const char* str); //替换从pos开始的n个字符为str

    6.比较操作:
        //compare 函数在大于时返回1,小于时返回-1,等于时返回0
        //比较区分大小写,比较时参考字典序,排越前面越小,大写的A比小写的a更小
        int compare(const char* str) const; //与字符串str比较
        int compare(const string& str) const; //与字符串str比较

    7.string子串:
        string substr(int pos = 0, int n = npos) const; //返回从pos开始的n个字符组成的字符串

    8.插入和删除操作:
        string& insert(int pos, const char* str); //从pos位置前方插入字符串
        string& insert(int pos, const string& str); //从pos位置前方插入字符串
        string& insert(int pos, int n, char c); //从pos前方插入n个字符c
        string& erase(int pos, int n = npos); //删除从pos开始的n个字符

    9.string 和 c-style 字符串转换
        const char* c_str(const string& str) const; //string转 c-style
        string string(const char* str); //c-style 转 string

    