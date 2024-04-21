一.构造函数和析构函数
1.构造函数
class Maker
{
public:
	//构造函数的作用是初始化成员变量,是编译器去调用的
	Maker()
	{
		b = 10;
	}
    //析构函数,当
    ~Maker()
public:
	int b;
};

void test()
{
	//实例化对象,内部做了两件事，(1).分配空间 (2)调用构造函数进行初始化
	Maker m;
	cout << m.b << endl;
}
int main()
{
	test();
	return EXIT_SUCCESS;
}

2.析构函数
class Maker
{
public:
	Maker(const char* Name,const char* Nickname)//有参构造
	{
        //从堆区申请空间
		name = (char*)malloc(strlen(Name) + 1);
		nickname = (char*)malloc(strlen(Nickname) + 1);
		strcpy(name, Name);
		strcpy(nickname, Nickname);
	}
	void print()
	{
		cout << "name:" << name << endl;
		cout << "nickname:" << nickname << endl;
	}
	~Maker()
	{
		if (name != nullptr || nickname != nullptr)//释放堆区空间
		{
			free(name);
			free(nickname);
			name = nullptr;
			nickname = nullptr;
		}
	}
private:
	char* name;
	char* nickname;
};

void test()
{
	Maker m("mcbwxg","迎难而上");
	m.print();
}
int main()
{
	test();
	return EXIT_SUCCESS;
}

-----------------------------------------------------------------------------------------------

二.构造函数和析构函数的注意
注意1:构造函数可以重载
class Maker
{
public:
    Maker()
    {
        
    }
    Maker(int a)
    {

    }
public:
    int b;
}

注意2:构造函数和析构函数必须是公有权限

注意3:类中存在默认的构造函数和析构函数
class  Maker
{
public:
   /* 
    Maker()  编译器提供的默认构造函数，函数体是空的
    {

    }
    ~Maker()   默认析构函数，函数体也是空的
    {

    }
    */
	void print()
	{
		a = 100;
		cout << a << endl;
	}
private:
	int a;
};

void test()
{
	Maker m;
	m.print();
}
int main()
{
	test();
	return EXIT_SUCCESS;
}

--------------------------------------------------------------------------------------------

三.拷贝构造函数(用一个已有的对象去初始化另一个对象)
class  Maker
{
public:
	Maker()
	{
		cout << "无参构造函数" << endl;
		a = 100;
	}
	Maker(const Maker &m)//构造函数重载  (如果不写,编译器也会有默认拷贝构造函数)
	{
		cout << "拷贝构造函数" << endl;
		a = m.a;
	}
	void print()
	{
		cout << "a = " << a << endl;
	}
public:
	int a;
};

void test()
{
	Maker m1;
	m1.print();
	Maker m2(m1);//传入要拷贝的对象
	m2.print();
}
int main()
{
	test();
	return EXIT_SUCCESS;
}

注意:拷贝构造函数的形参要用引用,即 Maker(const Maker &m)
若写成Maker(const Maker m)
则编译器会进行:1. Maker m2(m1);
              2. const Maker m2 = m1;
              3. const Maker m2(m1);//编译器认为
              4. const Maker m2 = m1;
              5. 进入死循环

----------------------------------------------------------------------------------------------------

四.匿名对象
1.匿名对象的生命周期在当前行

-----------------------------------------------------------------------------------------------------

五.拷贝构造函数的调用时机
1.对象以值的方式给函数参数
void func(Maker m) //隐藏了Maker m = m1;使用拷贝构造
{

}
void test()
{
	Maker m1;
	func(m1);
}

2.用一个已有的对象去初始化另一个对象
void test()
{
	Maker m1;
	Maker m2(m1);
}

3.函数的局部对象以值的方式从函数返回
//vs Debug模式下,会调用拷贝构造;而vs Release模式下不会调用拷贝构造;qt也不调用
Maker func()
{
	//局部对象
	Maker m;
	return m;
}
void test()
{
	Maker m1 = func();
}

------------------------------------------------------------------------------------------------------------------

六.构造函数的调用规则
1.如果程序员提供了有参构造函数,那么编译器不会提供默认构造函数,但是会提供默认拷贝构造函数
class Maker
{
public:
	Maker(int a)
	{

	}
}
void test()
{
	Maker m; //error,编译器不会提供默认构造函数

	Maker m(10);//正常,调用有参构造

	Maker m2(m);//正常,编译器提供拷贝构造函数
}

2.如果程序员提供了拷贝构造函数,那么编译器不会提供默认构造函数和默认拷贝构造函数

--------------------------------------------------------------------------------------

七.对象的深浅拷贝
1.默认的拷贝构造函数进行了简单的赋值操作(浅拷贝)

2.浅拷贝问题
同一块空间被释放2次
class  Student
{
public:
	Student(const char* Name,int Age)
	{
		pName = (char*)malloc(strlen(Name) + 1);
		strcpy(pName, Name);
		age = Age;
	}
	~Student()
	{
		if (pName != NULL)
		{
			free(pName);
			pName = NULL;
		}
	}
private:
	char* pName;
	int age;
};

void test()
{
	Student s1("mcbwxg", 18);
	Student s2(s1);
}
//test()结束时,先使用s1析构函数,释放Name;
//再使用s2析构函数,释放Name
//由于浅拷贝是简单的赋值,则s2.pName = s1.pName,导致两个地址相同,在释放时同一地址被释放了2次导致报错
int main()
{
	test();
	return EXIT_SUCCESS;
}

3.深拷贝解决浅拷贝问题
重写拷贝构造函数
class  Student
{
public:
	Student(const char* Name,int Age)
	{
		pName = (char*)malloc(strlen(Name) + 1);
		strcpy(pName, Name);
		age = Age;
	}
	Student(const Student& stu)
	{
		pName = (char*)malloc(strlen(stu.pName) + 1);
		strcpy(pName,stu.pName);
		age = stu.age;
	}
	~Student()
	{
		if (pName != NULL)
		{
			free(pName);
			pName = NULL;
		}
	}
private:
	char* pName;
	int age;
};

------------------------------------------------------------------------------------------

八.用new和delete代替malloc和free申请堆区空间
class Maker
{
public:
	Maker()
	{
		cout << "构造函数" << endl;
	}
	~Maker()
	{
		cout << "析构函数" << endl;
	}
};
void test()
{
	//用new的方式申请堆区空间，会调用类的构造函数
	Maker* m = new Maker;
	//用delete会调用类的析构函数
	delete m;
	m = nullptr;
}
int main()
{
	test();
	return EXIT_SUCCESS;
}

--------------------------------------------------------------------------------------------

九.new 和 delete 用于数组
1.new 创建基础类型的数组
void test()
{
	int* pInt = new int[5];
	char* pChar = new char[64];
	for (int i = 0; i < 5; i++) pInt[i] = i;//初始化
	//注意，如果new时有中括号，那么delete时也要加上中括号
	delete[] pInt;
	delete[] pChar;

}
int main()
{
	test();
	return EXIT_SUCCESS;
}

2.new 创建对象数组

---------------------------------------------------------------------------------------------

十.静态成员
class Maker
{
public:
	Maker()
	{

	}
public:
	//1.静态成员变量的生命周期是整个程序，作用域在类内
	static int a;
public:
	static void setA(int A) //5.静态成员函数只能访问静态成员变量，不能访问普通成员变量
	{
		a = A;
	}
};
//2.静态成员变量要在类内声明,在类外初始化
int Maker::a = 100;

void test()
{
	//3.静态成员变量属于类，不属于对象，是所有对象共享
	cout << Maker::a << endl;
	Maker m;
	cout << m.a << endl;
	//4.静态成员可以用类访问，也可以用对象访问
}
int main()
{
	test();
	return EXIT_SUCCESS;
}

-----------------------------------------------------------------------------------------

十一.this 指针
1.每一个对象都有一个隐藏的this指针,但不属于对象,是编译器添加的
2.编译器会把this指针传入成员函数内
3.this指针指向对象的存储空间
class Maker
{
public:
	Maker()
	{
		a = 10, b = 20;
	}
	void func()
	{
		cout << this->a << " " << this->b << endl;//this指针永远指向
	}
public:
	int a;
	int b;
};
void test()
{
	Maker m1, m2;
	m1.func();
	m2.func();
}
int main()
{
	test();
	return EXIT_SUCCESS;
}

this指针的作用
class Maker
{
public:
	void setA(int a)
	{
		this->a = a;//1.当形参名和成员变量名相同时,用this指针区分
	}
	Maker& getMaker()//2.返回对象本身
	{
		return *this;//重载运算符时有用
	}
public:
	int a;
};

---------------------------------------------------------------------------------------------

十二.常函数和常对象
1.常函数
(1).在函数的()后面加上const,这个函数就是常函数
(2).常函数内不能修改普通成员变量
(3).mutable修饰的成员变量在常函数内可以修改
class Maker
{
public:
	//常函数
	void myPrint()const//在函数后面加上const就是常函数
	{
		//a = 10;//error 常函数不能修改普通成员变量
		b = 200;
		cout << b << endl;
	}
public:
	int a;
	mutable int b;//mutable修饰的成员变量
};
void test()
{
	Maker m;
	m.myPrint();
}
int main()
{
	test();
	return EXIT_SUCCESS;
}

2.常函数
(1).在数据类型前面加上const,让对象成为常对象
const Maker m;
(2).常对象不能改变普通成员变量的值
(3).常对象不能调用普通成员函数
(4).常对象可以调用常函数
m.myPrint();

------------------------------------------------------------------------------
十三.友元的概念和友元函数
1.友元的概念
友元是赋予全局函数,类的成员函数,类有访问别的类的私有成员的权限

class Maker
{
	friend void test();//声明test()这个函数为Maker类的友元函数
public:
	Maker()
	{
		a = 10, b = 20;
	}
public:
	int a;
private:
	int b;
};
void test()
{
	Maker m;
	cout << m.a << endl;
	cout << m.b << endl;
}
int main()
{
	test();
	return EXIT_SUCCESS;
}

2.友元类
(1).通过传参来访问类的私有成员
class Maker01
{
	friend class Maker02;
public:
	Maker01()
	{
		val = 10;
	}
private:
	int val;
};

class Maker02
{
public:
	void myPrint(Maker01& m1)
	{
		cout << m1.val << endl;
	}
};

void test()
{
	Maker01 m1;
	Maker02 m2;
	m2.myPrint(m1);
}
int main()
{
	test();
	return EXIT_SUCCESS;
}

(2).通过类内指针来访问私有成员
class Maker02
{
public:
	Maker01* m1 = new Maker01;//赋予地址
	void func()
	{
		cout << m1->val << endl;
	}
};

------------------------------------------------------------------------------

十四.实现单例模式的思路
class Maker
{
public://静态成员函数访问静态成员
	static Maker* getPtr()//将pMaker传出去
	{
		if (pMaker == nullptr) pMaker = new Maker;
		else return pMaker;
	}
private:
	Maker() {}
	Maker(const Maker& m) {}
	~Maker() {}
private:
	static Maker* pMaker;//静态成员变量类内声明,类外初始化
};
Maker* Maker::pMaker = nullptr;//初始化
void test()
{
	Maker* m1 = Maker::getPtr();
	Maker* m2 = Maker::getPtr();
	cout << m1 << endl;
	cout << m2 << endl;
}
int main()
{
	test();
	return EXIT_SUCCESS;
}
