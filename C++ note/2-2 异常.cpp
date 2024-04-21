一.C++类型转换
1.静态转换(static_cast)
    1.用于类层次结构中父类和子类之间指针或引用的转换
        进行向上转型是安全的
        进行向下转型是不安全的
    //指针转换
    class Father
    {

    };
    class Son :public Father
    {

    };
    int main()
    {
	    Father* fa = nullptr;
	    Son* s = nullptr;
	    Son* s1 = static_cast<Son*>(fa);//向下转型,不安全
	    Father* fa1 = static_cast<Father*>(s);//向上转型,安全
	    return EXIT_SUCCESS;
    }

    //引用转换
    int main()
    {
	    Father f;
	    Son s;
	    Father& ref_f = f;
	    Son& ref_s = s;
	    static_cast<Father&>(ref_s);//向上转型
	    static_cast<Son&>(ref_f);//向下转型
	    return EXIT_SUCCESS;
    }

    2.用于基础数据类型之间的转换(int 转换成 char 之类的)
    int main()
    {
	    char a = 'a';
	    double d = static_cast<double>(a);
	    std::cout << d << std::endl;
	    return EXIT_SUCCESS;
    }

2.动态转换(dynamic_cast)
(1).dynamic_cast主要进行类层次间的向上转型和向下转型

(2).在类层次间进行向上转型(安全)时,dynamic_cast 和 static_cast 的效果是一样的

(3).在进行向下转型时,dynamic_cast 具有类型检查的功能,比 static_cast 更安全

(4).基础数据类型不能使用 dynamic_cast

(5).如果要使用 dynamic_cast 进行向下转型,则要发生多态
class Father
{
	virtual void func() {};
};
class Son :public Father
{
	virtual void func() {};
};
int main()
{
	Father* f = new Son;//父类指针指向子类对象,发生多态
	dynamic_cast<Son*>(f);//发生多态时,向下转换, 动态转换就可以认为安全
	return EXIT_SUCCESS;
}

3.常量转换(const_cast) 该运算符用来修改类型的 const 属性
(1).常量指针被转换为非常量指针,并且仍然指向原来的对象

(2).常量引用被转换为非常量引用,并且仍然指向原来的对象
注意:不能对非指针或非引用的变量使用 const_cast 操作符去直接移除它的 const 属性
int main()
{
	int* p = nullptr;
	const int* const_p = const_cast<const int*>(p);//给int*附加const属性

	const int* p_const = nullptr;
	int* pp = const_cast<int*>(p_const);//给const int*去除const属性
	return EXIT_SUCCESS;
}

4.重新解释转换(reinterpret_cast)
这是最不安全的转换机制,最有可能出问题
主要用于将一种数据类型转换成另一种数据类型
它可以将一个整数转换成一个指针,也可以将一个指针转换成一个整数
int main()
{
	int* p = nullptr;
	int a = 0;
	int d = 1;
	reinterpret_cast<int*>(a);//将int类型转换成指针
	reinterpret_cast<char*>(d);//将指针转换成int类型
	return EXIT_SUCCESS;
}

------------------------------------------------------------------------------------------------------------

二.异常的基本语法及流程
1.异常是什么:
一句话:异常处理就是处理程序中的错误,所谓错误是指程序运行时发生的一些异常事件(如:除0溢出,数组下标越界,所要读取的文件不存在,空指针,内存不足等等)

2.异常的基本语法:
int func(int a, int b)
{
	if (b == 0)
	{
		//2.抛出异常
		throw 10;//抛出一个int类型的异常
	}
	return a / b;
}
int main()
{
	int a = 10, b = 0;
	try //1.把有可能出现异常的代码块放入try中
	{
		func(a, b);
	}
	catch (int)//3.接收一个int类型的异常
	{
		std::cout << "抛出一个int类型的异常" << std::endl;
	}
	return EXIT_SUCCESS;
}

------------------------------------------------------------------------------------------------------------

三.异常的优势
1.异常可以抛出对象,对象中可以含有很多成员函数,有很多信息,可以让用户明白异常的原因
class Maker
{
public:
	void printMaker()
	{
		std::cout << "除数不能为0" << std::endl;
	}
};
int func(int a, int b)
{
	if (b == 0)
	{
		Maker m;
		throw m;
	}
	return a / b;
}
int main()
{
	int a = 10, b = 0;
	try 
	{
		func(a, b);
	}
	catch (int)
	{
		std::cout << "抛出一个int类型的异常" << std::endl;
	}
	catch (Maker maker)
	{
		std::cout << "抛出一个Maker类型的异常" << std::endl;
		maker.printMaker();
	}
	return EXIT_SUCCESS;
}

2.C语言的返回值可以忽略,但异常不能忽略,如果忽略给你报错

3.如果本层不想处理异常,可以在 catch 中 用 throw 向上抛出

------------------------------------------------------------------------------------------------

四.异常变量的生命周期
1.产生3个对象
class Maker
{
public:
	Maker() { std::cout << "Maker无参构造函数" << std::endl; }
	Maker(const Maker& m) { std::cout << "Maker拷贝构造函数" << std::endl; }
	~Maker() { std::cout << "Maker析构函数" << std::endl; }
};
int func(int a,int b)
{
	if (b == 0)
	{
		Maker m;//第一个对象产生,无参构造
		throw m;//第一个对象在throw时被析构
	}			//第二个对象产生, throw 时的m是上面的对象拷贝构造产生的
	return a / b;
}
void test()
{
	int a = 10, b = 0;
	try
	{
		func(a, b);
	}
	catch (Maker maker) //第三个对象maker产生,是上面抛出的m 进行拷贝构造产生的
	{
		std::cout << "接收一个Maker类型的异常" << std::endl;
		//最后两个对象在catch后被析构
	}
}

2.产生2个对象
class Maker
{
public:
	Maker() { std::cout << "Maker无参构造函数" << std::endl; }
	Maker(const Maker& m) { std::cout << "Maker拷贝构造函数" << std::endl; }
	~Maker() { std::cout << "Maker析构函数" << std::endl; }
};
int func(int a,int b)
{
	if (b == 0)
	{
		throw Maker();//第一个对象,匿名对象
	}
	return a / b;
}
void test()
{
	int a = 10, b = 0;
	try
	{
		func(a, b);
	}
	catch (Maker maker) //第二个对象maker产生,是上面抛出的匿名对象进行拷贝构造产生的
	{
		std::cout << "接收一个Maker类型的异常" << std::endl;
		//两个对象在catch后被析构
	}
}

3.产生1个对象(最常用)
class Maker
{
public:
	Maker() { std::cout << "Maker无参构造函数" << std::endl; }
	Maker(const Maker& m) { std::cout << "Maker拷贝构造函数" << std::endl; }
	~Maker() { std::cout << "Maker析构函数" << std::endl; }
};
int func(int a,int b)
{
	if (b == 0)
	{
		throw Maker();//第一个对象,匿名对象
	}
	return a / b;
}
void test()
{
	int a = 10, b = 0;
	try
	{
		func(a, b);
	}
	catch (Maker& maker) //如果加上引用则只有一个对象
	{
		std::cout << "接收一个Maker类型的异常" << std::endl;
		//对象在catch后被析构
	}
}

