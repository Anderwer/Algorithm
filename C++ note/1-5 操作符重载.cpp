一.运算符重载的概念
1.运算符重载,就是对已有的运算符重新进行定义,赋予其另一种功能,以适应不同的数据类型
2.运算符重载的目的是让语法更加简洁
3.运算符重载不能改变本来的寓意,不能改变基础类型的寓意
4.运算符重载的本质是另一种函数调用,是编译器去调用的
5.这个函数统一的名字叫operator
6.重载函数可以写成全局或成员函数
------------------------------------------------------------------------------------

二.加号\减号运算符重载
class Maker
{
public:
	Maker(int id, int age)
	{
		this->id = id;
		this->age = age;
	}
    //成员函数
    Maker operator+(Maker& m2)//写成成员函数,那么只需要一个参数,这个参数是运算符右边
    {
	return Maker(this->id + m2.id, this->age + m2.age);
    }
public:
	int id, age;
};
//全局方式
Maker operator+(Maker& m1, Maker& m2)//第一个参数是加号的左边,第二个参数是加号的右边
{
	return Maker(m1.id + m2.id, m1.age + m2.age);
}
void test()
{
	Maker m1(1, 18);
	Maker m2(2, 23);
	Maker m3 = m1 + m2;
	cout << "id:" << m3.id << endl;
	cout << "age:" << m3.age << endl;
}
int main()
{
	test();
	return EXIT_SUCCESS;
}

-------------------------------------------------------------------------------------------

三.左移\右移运算符重载
class Maker
{
public:
	Maker(int id, int age)
	{
		this->id = id;
		this->age = age;
	}
public:
	int id, age;
};
void operator<<(ostream& out, Maker& m)
{
	cout << m.id << " " << m.age << endl;
}
ostream& operator<<(ostream& out, Maker& m)//如果要和endl连用,那么要返回ostream对象
{
    cout << m.id << " " << m.age;
    return out;
}
void test()
{
	Maker m1(1, 18);
    cout << m1;
	cout << m1 << endl;
}
int main()
{
	test();
	return EXIT_SUCCESS;
}

-------------------------------------------------------------------------------------------------

四.赋值运算符重载
1.编译器给类提供了一个默认的赋值运算符重载函数
class Joker
{
public:
	Joker(const char* name)
	{
		pName = new char[strlen(name) + 1];
		strcpy(pName, name);
	}
	Joker& operator=(const char* name) //赋值运算符为什么要返回引用
	{								   //因为返回的时候如果不是引用,则会拷贝产生一个新的对象,而不是返回其本身
		if (!this->pName)			   //这违背了赋值原本的寓意
		{
			delete[] this->pName;
			this->pName = NULL;
		}
		this->pName = new char[strlen(name) + 1];
		strcpy(this->pName, name);
		return *this;
	}
	~Joker()
	{
		if (!pName)
		{
			delete[] pName;
			pName = NULL;
		}
	}
public:
	char* pName;
};
ostream& operator<<(ostream& out, Joker& j)
{
	cout << j.pName << endl;
	return out;
}
void test()
{
	Joker j1("mcbwxg");
	Joker j2("迎难而上");
	cout << j1 << j2;
	j1 = j2;
	cout << j1 << j2;
}
int main()
{
	test();
	return EXIT_SUCCESS;
}

-------------------------------------------------------------------------------------

五.前置加加\后置加加重载运算符
class Maker
{
public:
    Maker(int a)
    {
        this->a = a;
    }
    ~Maker() {}
    Maker& operator++()//前置加加
    {
        ++this->a;
        return *this;
    }
    Maker operator++(int)//后置加加,需要占位参数int,因为++是+1
    {
        Maker tmp = *this;
        ++this->a;
        return tmp;
    }
public:
    int a;
};
ostream& operator<<(ostream& out, Maker& m)
{
    cout << m.a;
    return out;
}
void test()
{
    Maker m(10);
    cout << ++m << endl;//打印11
	cout << m++ << endl;//打印11
	cout << m << endl;  //打印12
}
int main()
{
    test();
    return EXIT_SUCCESS;
}

----------------------------------------------------------------------------------------------------

六.数组下标重载
MyArray operator=(MyArray& arr)
{
    if (!pArray)
    {
        delete[] pArray;
        pArray = nullptr;
    }
    pArray = new int[arr.getCapacity()];
    for (int i = 0; i < arr.getSize(); i++) pArray[i] = arr[i];
    return *this;
}

int& operator[](int index)
{
    return pArray[index];
}

-----------------------------------------------------------------------------------------------------

七.智能指针类
1.智能指针类是管理另一个类的对象的释放
class Maker
{
public:
	Maker() { std::cout << "无参构造\n"; };
	~Maker() { std::cout << "析构函数\n"; };
};
class SmartPointer
{
public:
	SmartPointer(Maker* m)
	{
		this->pMaker = m;
		std::cout << "SmartPointer构造函数\n";
	}
	~SmartPointer()
	{
		std::cout << "SmartPointer析构函数\n";
		if (this->pMaker) {
			delete this->pMaker;
			this->pMaker = nullptr;
		}
	}
private:
	Maker* pMaker;
};
void test()
{
	Maker* m = new Maker;//堆区开辟空间
	SmartPointer sp(m);//栈区,会调用析构函数
					   //当test函数结束时会调用~SmartPointer
					   //在这析构函数中delete了Maker的对象 会调用Maker的析构函数
}
int main()
{
	test();
	return EXIT_SUCCESS;
}
