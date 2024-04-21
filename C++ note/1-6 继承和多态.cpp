一.继承的概念
1.继承的作用:
(1).代码复用
(2).扩展类的功能

2.继承方式:
(1).继承方式:公有继承,私有继承,保护继承
(2).子类从父类继承过来的成员的权限
    1.公有继承: 父类的公有属性成员,到子类还是公有属性
               父类的私有属性成员,到子类还是私有属性
               父类的保护属性成员,到子类还是保护属性
    
    2.保护继承: 父类的公有属性成员,到子类是保护属性
               父类的私有属性成员,到子类还是私有属性
               父类的保护属性成员,到子类还是保护属性

    3.私有继承: 父类的公有属性成员,到子类是私有属性
               父类的私有属性成员,到子类还是私有属性
               父类的保护属性成员,到子类是私有属性

--------------------------------------------------------------------------------------------------

二.继承中的构造函数和析构函数的调用
class Father
{
public:
	Father()
	{
		std::cout << "Father构造函数\n";
	}
	~Father()
	{
		std::cout << "Father析构函数\n";
	}
};
class Son :public Father
{
public:
	Son()
	{
		std::cout << "Son构造函数\n";
	}
	~Son()
	{
		std::cout << "Son析构函数\n";
	}
};
void test()
{
	Son s;
}
int main()
{
	test();
	return EXIT_SUCCESS;
}
得出:先调用Father的构造,再调用Son的构造;先调用Son的析构,再调用Father的析构

2.继承和组合混搭
得出:先调用父类构造,再调用成员对象的构造,最后调用自身构造,析构函数反之

------------------------------------------------------------------------------------------

三.继承中同名成员的处理方法
class Father
{
public:
	Father()
	{
		a = 10;
	}
public:
	int a;
};
class Son :public Father
{
public:
	Son()
	{
		a = 20;
	}
public:
	int a;
};
void test()
{
	Son s;
	std::cout << s.a << std::endl;//当子类的成员和父类同名时,父类的成员会被隐藏
	//如果想访问,则应加上作用域
	std::cout << s.Father::a << std::endl;
}
int main()
{
	test();
	return EXIT_SUCCESS;
}

----------------------------------------------------------------------------------------------

四.继承中静态成员的特性
1.静态成员可以被继承

2.继承中的静态静态成员同样会被同名的子类成员隐藏

------------------------------------------------------------------------------------------------

五.菱形继承
class GrandFather //被虚继承之后,基类则变为虚基类
{
public:
	GrandFather()
	{
		mA = 100;
	}
public:
	int mA;
};				//加上virtual关键字,转为虚继承
class Father1 :virtual public GrandFather
{

};
class Father2 :virtual public GrandFather
{

};
class Son :public Father1, public Father2 //菱形继承
{

};
void test()
{
	Son s;
	std::cout << s.mA << std::endl;//虚继承可以解决菱形继承中成员变量二义性问题
}
int main()
{
	test();
	return EXIT_SUCCESS;
}

-----------------------------------------------------------------------------------------------------

六.静态联编和动态联编
1.静态联编
编译器会根据函数调用的对象类型,在编译阶段就确定函数的调用地址,这就是静态联编

2.虚函数
在普通成员函数前面加上virtual关键字,该函数变为虚函数,是告诉编译器这个函数要晚绑定

3.动态联编
在运行阶段才确定要调用哪个函数(晚绑定)

4.动态联编的作用:可以晚绑定函数调用地址,这样可以扩充功能,不修改前面的代码的基础上进行项目的扩充

5.类型转换问题
	1.子类转换成父类(向上转型):编译器认为指针的寻址范围缩小了,所以转换是安全的
	2.父类转换成子类(向下转型):编译器认为指针的寻址范围扩大了,不安全

class Animal
{
public:
	virtual void speak()//不加virtual就是静态联编,其子类Dog,Dog1中的函数都会被调用成父类的speak
	{
		std::cout << "Animal Speak\n";
	}
};
class Dog :public Animal
{
public:
	void speak()
	{
		std::cout << "Dog Speak\n";
	}
};
class Dog1 :public Animal
{
	void speak()
	{
		std::cout << "Dog1 Speak\n";
	}
};
void doLogin(Animal* animal)//强制类型转换,因为Animal是Dog的父类,寻址范围变化安全,可以转换
{
	animal->speak();
}
void test()
{
	Animal* an = new Animal;
	Dog* D = new Dog;
	Dog1* D1 = new Dog1;
	doLogin(an);
	doLogin(D);
	doLogin(D1);//如果是静态联编,结果就是打印3遍Animal Speak
}
int main()
{
	test();
	return EXIT_SUCCESS;
}

-----------------------------------------------------------------------------------------------------

七.多态的基本概念
1.什么是多态:
同一个操作作用于不同的对象,可以有不同的解释,会产生不同的效果,这就是多态
class Person
{
public:
	virtual void speak()//虚函数
	{
		std::cout << "人\n";
	}
};
class P1 :public Person
{
public:
	virtual void speak()//重写父类虚函数
	{
		std::cout << "mcbwxg\n";
	}
};
class P2 :public Person
{
public:
	virtual void speak()//重写父类虚函数
	{
		std::cout << "迎难而上\n";
	}
};
void doLogin(Person* P)
{
	P->speak();
}
void test()
{
	Person* P = nullptr;
	P = new Person;
	doLogin(P);
	delete P;

	P = new P1;
	doLogin(P);
	delete P;

	P = new P2;
	doLogin(P);
	delete P;
}
int main()
{
	test();
	return EXIT_SUCCESS;
}
2.多态的作用:
	1.可以解决项目中的紧耦合问题,提供程序的可扩展性
	2.应用程序不必为每一个子类的功能编写代码,只需要对抽象的父类进行处理

3.多态发生的三个条件:
	1.有继承
	2.重写父类的虚函数
	3.父类的指针指向子类对象

---------------------------------------------------------------------------------------

八.多态的实现原理
class Person
{
public:
	virtual void speak()
	{
		std::cout << "Person\n";
	}
};
class P1 :public Person
{
public:
	virtual void speak()
	{
		std::cout << "P1\n";
	}
};

void test()
{
	Person* person = new P1;//向上转型			
	person->speak();//结果打印P1
}
int main()
{
	test();
	return EXIT_SUCCESS;
}
实现原理:
	1.编译器只要发现类中有虚函数,就会创建一张表,表里放类的所有虚函数的地址
	2.编译器会在类对象中安插一个虚函数表指针,指向这个类的虚函数表
	3.当编译器发现子类重写了父类的虚函数,那么子类重写的函数就会覆盖掉虚函数表中父类对应的函数
	4.当我们通过父类指针指向子类且去调用speak函数时(向上转型),编译器会根据Person对象中的虚函数表找到speak函数

---------------------------------------------------------------------------------------------------------------

九.纯虚函数和抽象类
1.依赖倒转
业务层依赖抽象层,实现层依赖抽象层
//抽象层
class rule
{
public:
	virtual int getnum(int a, int b) = 0;//纯虚函数
};

//实现层
class plus_rule :public rule
{
public:
	virtual int getnum(int a, int b)
	{
		return a + b;
	}
};
class miux_rule :public rule
{
public:
	virtual int getnum(int a, int b)
	{
		return a - b;
	}
};

//业务层
int doLogin(rule* r)
{
	int a = 10, b = 20;
	return r->getnum(a,b);
}

void test()
{
	rule* r = nullptr;
	r = new plus_rule;
	std::cout << doLogin(r) << std::endl;
	delete r;

	r = new miux_rule;
	std::cout << doLogin(r) << std::endl;
	delete r;
}
int main()
{
	test();
	return EXIT_SUCCESS;
}

2.开闭原则
对修改源代码关闭,对扩展新功能开放

3.纯虚函数
上述代码中virtual int getnum(int a, int b) = 0;就是纯虚函数

4.抽象类
	1.上述代码中有纯虚函数的类就是抽象类,不能实例化对象
	class rule
	{
	public:
		virtual int getnum(int a, int b) = 0;//纯虚函数
	};

	2.如果子类继承抽象类,子类必须实现抽象类的所有纯虚函数,不然子类也会变成抽象类
	class Father
	{
		virtual void func1() = 0;
		virtual void func2() = 0;
	};
	class Son :public Father
	{
		virtual void func1() {}
		virtual void func2() {}
	};
	void test()
	{
		Son s;//只有子类全部实现抽象类的纯虚函数,才能实例化子类对象
	}
	int main()
	{
		test();
		return EXIT_SUCCESS;
	}

---------------------------------------------------------------------------------------------

十.模版方法模式	
在抽象类中确定好函数的调用顺序
class Drink
{
public:
	virtual void Boil() = 0;//烧水
	virtual void Brew() = 0;//冲泡
	virtual void PourInCup() = 0;//倒入杯中
	virtual void Addsome() = 0;//加辅料

	//模版方法 把函数调用顺序确定下来
	void func()
	{
		Boil();
		Brew();
		PourInCup();
		Addsome();
	}
};
class Coffee :public Drink
{
public:
	virtual void Boil()
	{
		std::cout << "步骤一:煮水\n";
	}
	virtual void Brew()
	{
		std::cout << "步骤二:冲泡咖啡\n";
	}
	virtual void PourInCup()
	{
		std::cout << "步骤三:将咖啡倒入杯中\n";
	}
	virtual void Addsome()
	{
		std::cout << "步骤四:加入牛奶\n";
	}
};
class Tea :public Drink
{
public:
	virtual void Boil()
	{
		std::cout << "步骤一:煮水\n";
	}
	virtual void Brew()
	{
		std::cout << "步骤二:冲泡茶叶\n";
	}
	virtual void PourInCup()
	{
		std::cout << "步骤三:将茶水倒入杯中\n";
	}
	virtual void Addsome()
	{
		std::cout << "步骤四:加入菊花\n";
	}
};
void test()
{
	Drink* dk = nullptr;
	dk = new Coffee;
	dk->func();
	delete dk;
	std::cout << "--------------------------------\n";
	dk = new Tea;
	dk->func();
	delete dk;
}
int main()
{
	test();
	return EXIT_SUCCESS;
}

----------------------------------------------------------------------------------------

十一.虚析构函数和纯虚析构函数
1.虚析构函数是为了解决基类指针指向派生类对象,并用基类指针释放子类对象
class Father
{
public:
	Father()
	{
		std::cout << "Father构造函数\n";
	}
	virtual ~Father()//虚析构函数会去调用子类虚构函数
	{
		std::cout << "Father析构函数\n";
	}
};
class Son :public Father
{
public:
	Son()
	{
		std::cout << "Son构造函数\n";
	}
	~Son()
	{
		std::cout << "Son析构函数\n";
	}
};
void test()
{
	Father* f = new Son;
	delete f;
}
int main()
{
	test();
	return EXIT_SUCCESS;
}

2.纯虚析构函数,有纯虚析构函数的类是抽象类,不能实例化对象
注意:纯虚析构函数需要在类外实现
//上方代码改动
class Father
{
public:
	Father()
	{
		std::cout << "Father构造函数\n";
	}
	virtual ~Father() = 0;
};
Father::~Father()
{
	std::cout << "Father纯虚析构函数\n";
}

------------------------------------------------------------------------------------------

十二.父类引用子类对象
class Father
{
public:
	virtual void speak()
	{
		std::cout << "Father Speak\n";
	}
};

class Son :public Father
{
public:
	virtual void speak()
	{
		std::cout << "Son Speak\n";
	}
};
void test()
{
	Father& father = Son();//默认构造函数 //父类引用子类对象
	//Father& father = *new Son;
	father.speak();
}
int main()
{
	test();
	return EXIT_SUCCESS;
}