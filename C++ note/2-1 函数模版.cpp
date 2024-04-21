一.函数模版
1.什么是函数模版:
函数模版,实际上是建立一个通用函数,其函数类型和形参类型不具体指定,用一个虚拟的类型来代表,这个通用函数就成了函数模版

2.怎么编写函数模版
//T代表泛型的数据类型,不代表只能写T
template<class T> //让编译器看到这句话后面紧跟着的函数里的T不要报错
void mySwap(T &a, T &b)
{
	T tmp = a;
	a = b;
	b = tmp;
}
void test()
{
	double a = 10;
	double b = 20.5;
	mySwap(a, b);  //编译器会根据实参自动推导类型
    mySwap<double>(a,b);//也可以自己指定类型,用参数列表告诉编译器我只传入double类型
	std::cout << a << "\n" << b << "\n";
}
int main()
{
	test();
	return EXIT_SUCCESS;
}

3.编译器会对函数模板和类模板进行二次编译(将T换成确定的类型)

4.隐式转换
template<class T>
T func(T a, T b)
{
	return a + b;
}
void test()
{
	int a = 10;
	double b = 20.5;
	//如果使用参数列表指定类型,那么实参可以隐式转换
	//如果转换成功,则调用,转换不成功就报错
	std::cout << func<int>(a, b) << std::endl;
}
int main()
{
	test();
	return EXIT_SUCCESS;
}

----------------------------------------------------------------------------------------------------

二.普通函数和模版函数的调用规则
void myPrint(int a, int b)
{
	std::cout << "普通函数\n";
}
template<class T>
void myPrint(T a, T b)   
{
	std::cout << "模版函数\n";
}                             //1.模版函数和普通函数可以重载
void test()
{
	int a = 10, b = 20;
	myPrint(a, b);//2.如果模版函数和普通函数都可以实现功能,优先调用普通函数
	myPrint<>(a, b);//3.可以使用<>空参数列表强制调用模版函数

	char c1 = 'a', c2 = 'b';
	myPrint(c1, c2);//4.如果模版函数可以产生更好的匹配,那么优先调用模版函数
}
int main()
{
	test();
	return EXIT_SUCCESS;
}

---------------------------------------------------------------------------------------------------

三.类模版
1.类模版是把类中的数据类型参数化
template<class NameType,class AgeType>
class Person
{
public:
	Person(NameType name,AgeType age)
	{
		this->name = name;
		this->age = age;
	}
	void print()
	{
		std::cout << "Name:" << name << "\nAge:" << age;
	}
public:
	NameType name;
	AgeType age;
};
void test()
{
	Person<std::string,int> p("mcbwxg", 18); //类模版不会自动推导类型,要告诉编译器是什么类型
	p.print();
}
int main()
{
	test();
	return EXIT_SUCCESS;
}

-------------------------------------------------------------------------------------------------------

四.类模版的继承
1.普通类继承类模版
 template<class T>
class Person
{
public:
	T age;
};
class Son :public Person<int> //要告诉编译器父类的参数类型
{

};

2.类模版继承类模版
template<class T>
class Person
{
public:
	T age;
};
template<class T>
class Son :public Person<T> 
{

};

---------------------------------------------------------------------------------------------------

五.类模版的成员函数类外实现
template<class NameType, class AgeType>
class Person
{
public:
	Person(NameType name, AgeType age);
	void print();
public:
	NameType name;
	AgeType age;
};

template<class NameType, class AgeType>         //模版类的成员函数类外实现
Person<NameType, AgeType>::Person(NameType name, AgeType age)
{
	this->age = age;
	this->name = name;
}
template<class NameType, class AgeType>
void Person<NameType, AgeType>::print()
{
	std::cout << "Name:" << name << "\nAge:" << age;
}

void test()
{
	Person<std::string, int> p("mcbwxg", 18); 
	p.print();
}
int main()
{
	test();
	return EXIT_SUCCESS;
}

------------------------------------------------------------------------------------------------

六.类模版分文件编写问题及解决办法
1.调用类模版时,要进行第二次编译,要把泛型的数据类型替换成具体的数据类型,这时需要知道函数体,但是该函数的实现在.cpp中,当调用类模版的.cpp时没有引入实现.cpp,只有.h,所以报错

2.解决办法:把成员函数放到.hpp中,然后在调用成员函数的地方引入.hpp

3.为什么.hpp中有成员函数的实现,然后在调用类模版的地方引入.hpp时不会重定义报错
因为类的成员函数默认申请成为内联函数,在链接时,链接器会对重复的成员函数进行处理,只保留一份成员函数,所以不会报错

举例:
Person.hpp ->

#include<iostream>
#include<string>
template<class NameT,class AgeT>  //类模版声明
class Person  
{
public:
	Person(NameT name,AgeT age);
	~Person();
	void print();
public:
	NameT name;
	AgeT age;
};
                                    //类模版的实现
template<class NameT, class AgeT>
Person<NameT, AgeT>::Person(NameT name,AgeT age)
{
	this->name = name;
	this->age = age;
}

template<class NameT, class AgeT>
Person<NameT, AgeT>::~Person()
{
	delete this;
}

template<class NameT, class AgeT>
void Person<NameT, AgeT>::print()
{
	std::cout << "Name:" << name << "\nAge:" << age << std::endl;
}

main.cpp ->

#include"Person.hpp"
void test()
{
	Person<std::string, int>* p = new Person<std::string, int>("Person", 18);
	p->print();
	p = nullptr;
}
int main()
{
	test();
	return EXIT_SUCCESS;
}

-----------------------------------------------------------------------------------------------

七.类模版和友元
1.友元类内实现
template<class NameT, class AgeT>  
class Person
{
	friend void print(Person<NameT, AgeT>& P)//友元函数类内实现
	{
		std::cout << "Name:" << P.name << "\nAge:" << P.age << std::endl;
	}
public:
	Person(NameT name, AgeT age)
	{
		this->name = name;
		this->age = age;
	}
private:
	NameT name;
	AgeT age;
};
void test()
{
	Person<std::string,int> p("Person",18);
	print(p);
}
int main()
{
	test();
	return EXIT_SUCCESS;
}

2.友元类外实现
//1.声明类模版
template<class NameT, class AgeT>
class Person;
//2.声明函数模版
template<class NameT, class AgeT>
void print(Person<NameT, AgeT>& p);
//3.类的实现
template<class NameT, class AgeT>  
class Person
{   //4.声明友元函数,且加空参数列表<>强制调用函数模版
	friend void print<>(Person<NameT,AgeT>& p);
public:
	Person(NameT name, AgeT age)
	{
		this->name = name;
		this->age = age;
	}
private:
	NameT name;
	AgeT age;
};
//5.函数模版的实现
template<class NameT,class AgeT>
void print<>(Person<NameT, AgeT>& p)
{
	std::cout << "Name:" << p.name << "\nAge:" << p.age << std::endl;
}
void test()
{
	Person<std::string,int> p("Person",18);
	print(p);
}
int main()
{
	test();
	return EXIT_SUCCESS;
}

-----------------------------------------------------------------------------------------------------
