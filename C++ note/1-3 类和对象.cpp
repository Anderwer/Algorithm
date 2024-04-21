一.类的封装
1.封装就是把属性(变量)和方法(函数)封装到类内,然后给这些数据赋予权限

2.为什么要有封装:
(1).防止乱调用函数和变量,出现错误
(2).维护代码更方便

3.权限
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
using namespace std;

class Maker
{
public://公有权限
	void set(int ID,string Name)
	{
		id = ID;
		name = Name;
	}
	void myprint()
	{
		cout << "姓名:" << name << "\n学号:" << id << endl;
	}
public:
	int id;
	string name;
private://私有权限
	int a;
	int b;
protected://保护权限
	int c;
};

class Son :public Maker //子类的类内可以访问父类的保护权限的成员
{
public:
	void func()
	{
		//a = 20;不在保护权限内,报错
		c = 20;
		cout << c << endl;
	}
};
//类外不能访问私有权限的成员
//类外可以访问公有权限的成员
//类外不能访问保护权限的成员
//子类的类内可以访问父类的保护权限的成员
//类内没有权限之分
void test()
{
	Maker m;
	m.set(1, "mcbwxg");
	m.myprint();
	Son s;
	s.func();
}
int main()
{
	test();
	return EXIT_SUCCESS;
}